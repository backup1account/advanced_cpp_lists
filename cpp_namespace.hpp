#ifndef CPP_NAMESPACE_HPP
#define CPP_NAMESPACE_Hpp

#include <future>
#include <thread>
#include <iostream>
#include <mutex>

#include "vector.hpp"
#include "unique_ptr.hpp"
#include "thread_pool.hpp"
#include "non0_ptr.hpp"

#include "FuelTank.hpp"
#include "Engine.hpp"

namespace cpplab {
    template<typename T, typename T2>
    auto add(const T &a, const T2 &b) -> decltype(a + b) {
        return (a + b);
    }

    template<typename T, typename T2, 
            typename = std::enable_if_t< std::is_pointer_v<T> && std::is_pointer_v<T2>>,
            typename = std::enable_if_t< !std::is_same_v<T, const char*> && !std::is_same_v<T2, const char*> >>
    auto add(const T a, const T2 b) -> decltype(*a + *b) {
        return (*a + *b);
    }

    template<typename T, typename T2,
             typename = std::enable_if_t< std::is_same_v<T, const char*> && std::is_same_v<T2, const char*> >>
    auto add(const T a, const T2 b) {
        return std::string(a)+b;
    }

    template<typename T, typename T2, typename U>
    auto alias(const T &a, const T2 &b, U operation) -> decltype(operation(a, b)) {
        return operation(a, b);
    }

    template<typename T, const T B, const int W,
            typename = std::enable_if_t< std::is_arithmetic_v<T> >>
    class hyperqube {
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

    auto ThreadGenerator(int& id) 
    {
        std::cout << "Thread created with id " << id << '\n';
        return id++;
    }

    void printThread(std::string param, int thread_id) {
        static std::mutex mx;
        const std::lock_guard<std::mutex> lock(mx);
        std::cout << "Working on thread with id " << thread_id << '\n';
        std::cout << param << '\n';
    }

    void asyncInformation(std::string description, std::string launch_type){
        std::cout << description << " type: " << launch_type << "\n";
    }

    auto print_info(std::launch policy) {
        std::string launch_type = "async";

        if(policy == std::launch::deferred){
            launch_type = "deffered";
        }

        auto async_obj = std::async(policy, asyncInformation, "First nested call started with policy ", launch_type);
        async_obj.get();
    }

    auto print_info2(std::launch policy) {
        std::string launch_type = "async";

        if(policy == std::launch::deferred){
            launch_type = "deffered";
        }

        auto async_obj = std::async(policy, asyncInformation, "Second nested call started with policy ", launch_type);
        print_info(policy);
        async_obj.get();
    }

    auto print_info3(std::launch policy) {
        std::string launch_type = "async";

        if(policy == std::launch::deferred){
            launch_type = "deffered";
        }

        auto async_obj = std::async(policy, asyncInformation, "Third nested call started with policy ", launch_type);
        print_info2(policy);
        async_obj.get();
    }
}

#endif