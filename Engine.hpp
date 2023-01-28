#ifndef CPP_ENGINE_HPP
#define CPP_ENGINE_HPP

#include <thread>
#include <mutex>
#include <list>
#include <condition_variable>

namespace cpplab {
    class Engine;
}

class cpplab::Engine {
    public:
    Engine(unsigned int interval, unsigned int fuelAmount)
        : interval(interval), fuelAmount(fuelAmount) {
        thread = std::thread([&] {
            while (true) {
                std::unique_lock<std::mutex> lock(mtx);
                cv.wait(lock, [this] { return tanks.empty() || !tanks.empty(); });

                if (tanks.empty()) {
                    break;
                }

                for (auto it = tanks.begin(); it != tanks.end(); ++it) {
                    unsigned int taken = (*it)->refuel(fuelAmount);
                    if (taken > 0) break;
                    it = tanks.erase(it);
                }

                lock.unlock();
                std::this_thread::sleep_for(std::chrono::seconds(interval));
            }
        });
    }

    ~Engine() {
        thread.join();
    }

    void connectTank(std::shared_ptr<cpplab::FuelTank> tank) {
        std::unique_lock<std::mutex> lock(mtx);
        tanks.push_back(tank);
        cv.notify_one();
        lock.unlock();
    }

    private:
    std::thread thread;
    std::list<std::shared_ptr<cpplab::FuelTank>> tanks;
    std::mutex mtx;
    std::condition_variable cv;
    unsigned int interval, fuelAmount;
};

#endif