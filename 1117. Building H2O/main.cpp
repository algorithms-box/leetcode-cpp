#include <atomic>
#include <cassert>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

class H2O {
  private:
    mutex mtx;
    condition_variable cv;
    atomic<int> hydrogenCount{0};
    atomic<int> oxygenCount{0};

  public:
    H2O() {}

    void hydrogen(function<void()> releaseHydrogen) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this] { return hydrogenCount < 2; });

        releaseHydrogen();

        hydrogenCount++;
        if (hydrogenCount == 2 && oxygenCount == 1) {
            hydrogenCount = 0;
            oxygenCount = 0;
        }
        cv.notify_all();
    }

    void oxygen(function<void()> releaseOxygen) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this] { return oxygenCount == 0; });

        releaseOxygen();

        oxygenCount++;
        if (hydrogenCount == 2 && oxygenCount == 1) {
            hydrogenCount = 0;
            oxygenCount = 0;
        }
        cv.notify_all();
    }
};

// 用于测试的全局变量
atomic<int> hydrogenReleased{0};
atomic<int> oxygenReleased{0};

void releaseHydrogen() {
    hydrogenReleased++;
    cout << "H";
}

void releaseOxygen() {
    oxygenReleased++;
    cout << "O";
}

// 单元测试
void runUnitTest() {
    H2O h2o;
    vector<thread> threads;

    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([&h2o]() { h2o.hydrogen(releaseHydrogen); });
        threads.emplace_back([&h2o]() { h2o.hydrogen(releaseHydrogen); });
        threads.emplace_back([&h2o]() { h2o.oxygen(releaseOxygen); });
    }

    for (auto &t : threads) {
        t.join();
    }

    cout << endl;
    assert(hydrogenReleased == 20 && "Hydrogen should be released 20 times");
    assert(oxygenReleased == 10 && "Oxygen should be released 10 times");
    cout << "Unit test passed!" << endl;
}

// 性能测试
void runPerformanceTest() {
    H2O h2o;
    vector<thread> threads;
    const int iterations = 100000;

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i) {
        threads.emplace_back([&h2o]() { h2o.hydrogen([]() {}); });
        threads.emplace_back([&h2o]() { h2o.hydrogen([]() {}); });
        threads.emplace_back([&h2o]() { h2o.oxygen([]() {}); });
    }

    for (auto &t : threads) {
        t.join();
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    cout << "Performance test: " << iterations << " H2O molecules formed in "
         << duration.count() << " ms" << endl;
}

int main() {
    runUnitTest();
    runPerformanceTest();
    return 0;
}