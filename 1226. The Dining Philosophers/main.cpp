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

class DiningPhilosophers {
  private:
    vector<mutex> forks;
    mutex m;
    condition_variable cv;
    vector<bool> eating;

  public:
    DiningPhilosophers() : forks(5), eating(5, false) {}

    void wantsToEat(int philosopher, function<void()> pickLeftFork,
                    function<void()> pickRightFork, function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {
        int left = philosopher;
        int right = (philosopher + 1) % 5;

        {
            unique_lock<mutex> lock(m);
            cv.wait(lock, [this, left, right] {
                return !eating[left] && !eating[right];
            });
            eating[left] = eating[right] = true;
        }

        forks[left].lock();
        forks[right].lock();

        pickLeftFork();
        pickRightFork();
        eat();
        putLeftFork();
        putRightFork();

        forks[right].unlock();
        forks[left].unlock();

        {
            lock_guard<mutex> lock(m);
            eating[left] = eating[right] = false;
        }
        cv.notify_all();
    }
};

// 单元测试
void unitTest() {
    DiningPhilosophers dp;
    vector<int> eatCount(5, 0);
    vector<thread> threads;

    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([&dp, i, &eatCount] {
            for (int j = 0; j < 100; ++j) {
                dp.wantsToEat(
                    i, []() {}, []() {}, [i, &eatCount]() { eatCount[i]++; },
                    []() {}, []() {});
            }
        });
    }

    for (auto &t : threads) {
        t.join();
    }

    for (int i = 0; i < 5; ++i) {
        assert(eatCount[i] == 100);
        cout << "Philosopher " << i << " ate " << eatCount[i] << " times."
             << endl;
    }
    cout << "Unit test passed successfully!" << endl;
}

// 性能测试
void performanceTest() {
    DiningPhilosophers dp;
    vector<thread> threads;
    atomic<int> totalEats(0);

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([&dp, i, &totalEats] {
            for (int j = 0; j < 10000; ++j) {
                dp.wantsToEat(
                    i, []() {}, []() {}, [&totalEats]() { totalEats++; },
                    []() {}, []() {});
            }
        });
    }

    for (auto &t : threads) {
        t.join();
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    cout << "Performance test: " << totalEats << " total eats in "
         << duration.count() << " ms" << endl;
}

int main() {
    unitTest();
    performanceTest();
    return 0;
}