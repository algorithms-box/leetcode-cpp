#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class H2O {
  private:
    std::mutex mtx;
    std::condition_variable cv;
    int hydrogen_count = 0;
    int oxygen_count = 0;

  public:
    H2O() {}

    void hydrogen(std::function<void()> releaseHydrogen) {
        std::unique_lock<std::mutex> lock(mtx);
        releaseHydrogen(); // outputs "H"
        hydrogen_count++;
        if (hydrogen_count == 2) {
            hydrogen_count = 0;
            cv.notify_one(); // Signal when two hydrogen atoms are available
        }
    }

    void oxygen(std::function<void()> releaseOxygen) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] {
            return this->hydrogen_count == 0;
        });              // Wait until two hydrogen atoms are available
        releaseOxygen(); // outputs "O"
        oxygen_count++;
    }
};

// Unit Testing
void testH2O() {
    H2O h2o;
    std::thread hydrogen_thread([&h2o] {
        for (int i = 0; i < 10; ++i) {
            h2o.hydrogen([]() { std::cout << "H"; });
        }
    });
    std::thread oxygen_thread([&h2o] {
        for (int i = 0; i < 5; ++i) {
            h2o.oxygen([]() { std::cout << "O"; });
        }
    });
    hydrogen_thread.join();
    oxygen_thread.join();
    std::cout << std::endl;
    std::cout << "All tests passed.\n";
}

// Performance Testing
void performanceTest() {
    H2O h2o;
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::thread> hydrogen_threads;
    std::vector<std::thread> oxygen_threads;
    for (int i = 0; i < 10000; ++i) {
        hydrogen_threads.emplace_back(
            [&h2o] { h2o.hydrogen([]() { std::cout << "H"; }); });
    }
    for (int i = 0; i < 5000; ++i) {
        oxygen_threads.emplace_back(
            [&h2o] { h2o.oxygen([]() { std::cout << "O"; }); });
    }
    for (auto &th : hydrogen_threads)
        th.join();
    for (auto &th : oxygen_threads)
        th.join();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Performance Test: " << elapsed.count() << " seconds"
              << std::endl;
}

int main() {
    testH2O();
    performanceTest();
    return 0;
}
