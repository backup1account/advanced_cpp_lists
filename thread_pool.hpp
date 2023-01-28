// #ifndef CPP_THREAD_POOL_HPP
// #define CPP_THREAD_POOL_HPP

// #include <vector>
// #include <thread>
// #include <mutex>
// #include <condition_variable>

// namespace cpplab {
//     class ThreadPool;
// };

// class cpplab::ThreadPool {
//     private:
//     using Task = std::function<double>;

//     std::vector<std::thread> mThreads;
//     std::vector<Task> mTasks;
//     std::mutex mTasksMutex;
//     std::condition_variable mTasksCV;

//     bool mStopping = false;

//     public:
//     explicit ThreadPool(size_t thread_num) 
//     {
//         for (size_t i = 0; i < thread_num; ++i)
//         {
//             mThreads.emplace_back(
//                 std::thread([this]()
//                 {
//                     std::unique_lock<std::mutex> lock{mTasksMutex};
//                     mTasksCV.wait(lock, [=] { return mStopping || !mTasks.empty(); });

//                     // if (mStopping) { break; }

//                 })
//             );
//         }
//     }

//     ~ThreadPool()
//     {
//         stop();
//     }

//     void add_task(Task task)
//     {

//         mTasks.emplace_back(std::move(task));
//     }

//     double average()
//     {

//     }

//     void stop()
//     {


//         for(auto& t: mThreads)
//         {
//             t.join();
//         }
//     }
// };

// #endif