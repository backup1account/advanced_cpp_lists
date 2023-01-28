#ifndef CPP_THREAD_POOL_HPP
#define CPP_THREAD_POOL_HPP

#include <vector>
#include <queue>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <future>


namespace cpplab {
    class ThreadPool;
}

class cpplab::ThreadPool {
    private:
    std::vector<std::thread> pool;
    std::queue<std::function<double()>> tasks;
    std::vector<double> results;
    std::mutex queue_mutex;
    std::condition_variable cv;
    bool m_stop = false;

    public:
    explicit ThreadPool(int numThreads);

    ~ThreadPool();

    void add_task(std::function<double()> task);

    double average();

    void stop();
};

#endif