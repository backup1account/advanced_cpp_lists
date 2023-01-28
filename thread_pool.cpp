#include "thread_pool.hpp"


cpplab::ThreadPool::ThreadPool(int numThreads)
{
    for (int i = 0; i < numThreads; ++i) {
        pool.emplace_back([this] {
            while (true) {
                std::function<double()> task;
                {
                    std::unique_lock<std::mutex> lock(queue_mutex);
                    cv.wait(lock, [this] { return m_stop || !tasks.empty(); });
                    if (m_stop && tasks.empty()) {
                        return;
                    }
                    task = std::move(tasks.front());
                    tasks.pop();
                }
                results.push_back(task());
            }
        });
    }
}


cpplab::ThreadPool::~ThreadPool()
{
    stop();
}


void cpplab::ThreadPool::add_task(std::function<double()> task) 
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        tasks.emplace(task);
    }
    cv.notify_one();
}


double cpplab::ThreadPool::average() 
{
    double avg = 0;
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        int n = results.size();
        for (double result : results) {
            avg += result / n;
        }
    }
    return avg;
}


void cpplab::ThreadPool::stop() 
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        m_stop = true;
    }

    cv.notify_all();
    for (auto &thread : pool) {
        thread.join();
    }
}