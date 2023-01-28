#ifndef CPP_NAMESPACE_HPP
#define CPP_NAMESPACE_HPP

#include <thread>
#include <mutex>
#include <future>

namespace cpplab {
    template<typename T, typename T2>
    auto add(const T &a, const T2 &b) -> decltype(a + b)
    {
        return (a + b);
    }

    template<typename T, typename T2, 
            typename = std::enable_if_t< std::is_pointer_v<T> && std::is_pointer_v<T2>>,
            typename = std::enable_if_t< !std::is_same_v<T, const char*> && !std::is_same_v<T2, const char*> >>
    auto add(const T a, const T2 b) -> decltype(*a + *b) 
    {
        return (*a + *b);
    }

    template<typename T, typename T2,
             typename = std::enable_if_t< std::is_same_v<T, const char*> && std::is_same_v<T2, const char*> >>
    auto add(const T a, const T2 b) 
    {
        return std::string(a)+b;
    }

    template<typename T, typename T2, typename U>
    auto alias(const T &a, const T2 &b, U operation) -> decltype(operation(a, b)) 
    {
        return operation(a, b);
    }

    template<typename T, const T B, const int W,
            typename = std::enable_if_t< std::is_arithmetic_v<T> >>
    class hyperqube 
    {
        public:
        static constexpr auto volume = (W >= 0) ? pow(B, W) : -1;
    };

    template <typename T, typename... Args>
    auto add_total(T value, Args... args)
    {
        if constexpr (sizeof...(args) == 0) {
            return value;
        } else {
            return value + (args + ...);
        }
    }

    void printThread(std::string param, int thread_id) 
    {
        static std::mutex mx;
        const std::lock_guard<std::mutex> lock(mx);
        std::cout << "Working on thread with id " << thread_id << '\n';
        std::cout << param << '\n';
    }

    void printAsyncInformation(std::string launch_info)
    {
        std::cout << "Launch type information: " << launch_info << '\n';
    }

    void async1(std::launch launch_info)
    {
        // if (launch_info)
        // std::async(std::launch::async, printAsyncIn formation, launch_info);
    }

    class ThreadPool {
        private:
        using Task = std::function<double>;

        std::vector<std::thread> mThreads;
        std::vector<Task> mTasks;
        std::mutex mTasksMutex;
        std::condition_variable mTasksCV;

        bool mStopping = false;

        public:
        explicit ThreadPool(size_t thread_num) 
        {
            for (size_t i = 0; i < thread_num; ++i)
            {
                mThreads.emplace_back(
                    std::thread([this]()
                    {
                        std::unique_lock<std::mutex> lock{mTasksMutex};
                        mTasksCV.wait(lock, [this] { return mStopping || !mTasks.empty(); });

                        // if (mStopping) { break; }

                    })
                );
            }
        }
        
        ~ThreadPool()
        {
            stop();
        }

        // void add_task(Task task)
        // {

        //     mTasks.emplace_back(std::move(task));
        // }

        // double average()
        // {

        // }

        void stop()
        {


            for(auto& t: mThreads)
            {
                t.join();
            }
        }

    };

}

#endif