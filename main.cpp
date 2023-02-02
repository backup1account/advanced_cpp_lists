#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <thread>

#include "cpp_namespace.hpp"

struct Pixel
{
    public:
    int r = 0;
    int g = 0;
    int b = 0;

    Pixel() = default;
    Pixel(int r, int g, int b) : r(r), g(g), b(b) {}
    ~Pixel() = default;
};

auto ScalarProduct(std::vector<double>& v1, std::vector<double>& v2, std::promise<double> s_promise)
{
    double result = 0.0;

    if ((v1.size() != v2.size()) || v1.empty() || v2.empty()) 
    {
        s_promise.set_exception(std::exception_ptr(std::make_exception_ptr(std::runtime_error("Invalid vector"))));
    }
    else
    {
        for (size_t i = 0; i < v1.size(); ++i)
        {
            result += v1[i] * v2[i];
        }

        s_promise.set_value(result);
    }
}



int main() {
    // ____________ LIST 1 ____________

    // std::cout << cpplab::add(3.444, 56) << '\n';
    // std::cout << cpplab::add<std::string>("aaa", "bcdef") << '\n';

    // auto sum = [] (auto a, auto b) { return a+b; };
    // auto max = [] (auto a, auto b) { return (a>b ? a : b); };

    // std::cout << cpplab::alias(34, 543.23456, sum) << '\n';
    // std::cout << cpplab::alias(4, 44, max) << '\n';
    // std::cout << cpplab::alias(44, 65, max) << '\n';


    // int example_size = 4;
    // auto a = cpplab::vector<int>(example_size);
    // auto v = std::vector<int>{3,4,5,5,6};

    // a.push(4);
    // a.pop();

    // for(int i=0; i < example_size; ++i) {
    //     std::cout << a[i] << '\n';
    // }

    // std::cout << a * v << '\n';
    
    // ____________ LIST 2 ____________

    // int b1 = 4;
    // int b2 = 5;
    // int *a = &b1;
    // int *c = &b2;

    // const char *text1 = "alamakota";
    // const char *text2 = "itymbarka";

    // std::cout << cpplab::add(text1, text2) << '\n';

    // std::cout << cpplab::add(b1, b2) << '\n';
    // std::cout << cpplab::add(a, c) << '\n';

    // std::cout << cpplab::hyperqube<int, 3, 4>::volume << '\n';
    // std::cout << cpplab::hyperqube<int, 2, 6>::volume << "\n";

    // std::cout << cpplab::add_total(1, 1.0, 1.0f) << '\n';
    // std::cout << cpplab::add_total(1.5, 13, 16.0f, 4) << '\n';

    // ____________ LIST 3 ____________

    // auto vector1 = cpplab::vector<int>(5);
    // auto copy_vector1 = vector1;
    // auto move_vector1 = std::move(vector1);

    // std::cout << copy_vector1.size() << '\n';
    // std::cout << move_vector1.size() << '\n';
    // std::cout << vector1.size() << '\n';

    // for (int i=0; i < 5; ++i) {
    //     std::cout << copy_vector1[i] << '\n';
    // }

    // for (int i=0; i < 5; ++i) {
    //     std::cout << move_vector1[i] << '\n';
    // }


    // auto temp_vector = cpplab::vector<Pixel>();
    // temp_vector.emplace_back(2,3,4);

    // for (size_t i = 0; i < temp_vector.size(); i++)
    // {
    //     std::cout << temp_vector[i].r << " " << temp_vector[i].g << " " << temp_vector[i].b << "\n";
    // }

    // temp_vector.emplace_back(2,3,4);

    // ____________ LIST 5 ____________

    // int threadId = 0;

    // std::thread thread_obj(cpplab::printThread, "Here's text", cpplab::ThreadGenerator(threadId));
    // std::thread thread_obj2(cpplab::printThread, "Here's text 2", cpplab::ThreadGenerator(threadId));
    // std::thread thread_obj3(cpplab::printThread, "Here's text 34", cpplab::ThreadGenerator(threadId));
    
    // thread_obj.join();
    // thread_obj2.join();
    // thread_obj3.join();

    // cpplab::print_info(std::launch::async); 
    // cpplab::print_info2(std::launch::deferred);


    // ____________ LIST 6 ____________

    std::vector<double> vec1 {1,2,3};
    std::vector<double> vec2 {4,5,6};

    try {
        std::vector<std::thread> thread_vec;

        double result_t = 0.0;

        for (size_t i = 0; i < 10; i++)
        {
            std::promise<double> s_promise;
            std::future<double> s_future = s_promise.get_future();

            thread_vec.push_back( std::thread { ScalarProduct, ref(vec1), ref(vec2), std::move(s_promise) } );

            try
            {
                result_t += s_future.get();
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            
        }

        std::cout << result_t << '\n';

        for (auto& element : thread_vec)
        {
            element.join();
        }
    } 
    catch(std::exception& e) {
        std::cout << e.what() << '\n';
    }

    // ____________ LIST 7 ____________

    // cpplab::ThreadPool pool(5);

    // for (int i = 0; i < 5; i++) {
    //     pool.add_task([i] {
    //         std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //         std::cout << "Iteration nr. " << i << '\n';
    //         return i;
    //     });
    // }

    // pool.stop();
    // std::cout << "Average value of the results: " << pool.average() << std::endl;


    // ____________ LIST 8 ____________

    // std::vector<std::shared_ptr<cpplab::FuelTank>> tanks;

    // for (int i = 0; i < 10; ++i) {
    //     tanks.push_back(std::make_shared<cpplab::FuelTank>(10));
    // }

    // cpplab::Engine engine1(2, 5);
    // cpplab::Engine engine2(1, 1);
    // cpplab::Engine engine3(3, 2);

    // for (auto &tank : tanks) {
    //     engine1.connectTank(tank);
    //     engine2.connectTank(tank);
    //     engine3.connectTank(tank);
    // }

    // std::this_thread::sleep_for(std::chrono::seconds(10));

    // cpplab::unique_ptr<int> p1(new int(33));
    // std::cout << *p1 << std::endl; // prints 33

    // cpplab::unique_ptr<int> p2 = p1.release();
    // std::cout << *p2 << std::endl; // prints 33

    // p1.reset(new int(15));
    // std::cout << *p1 << std::endl; // prints 15

    // int x = 100;
    // cpplab::non0_ptr<int> ptr1 {&x};
    // std::cout << *ptr1 << '\n';

    // try {
    //     cpplab::non0_ptr<int> ptr2 {nullptr};
    // } catch (const std::runtime_error& e) {
    //     std::cout << "Caught exception: " << e.what() << '\n';
    // }

    return 0;
}