#include <atomic>
#include <cassert>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class Foo {
  private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;

  public:
    Foo() : count(0) {}

    void first(const std::function<void()> &printFirst) {
        std::unique_lock<std::mutex> lock(mtx);
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        count++;
        cv.notify_all();
    }

    void second(const std::function<void()> &printSecond) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return count >= 1; });
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        count++;
        cv.notify_all();
    }

    void third(const std::function<void()> &printThird) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return count >= 2; });
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};

void runUnitTest() {
    Foo foo;
    std::vector<std::string> output;

    auto printFirst = [&output]() { output.push_back("first"); };
    auto printSecond = [&output]() { output.push_back("second"); };
    auto printThird = [&output]() { output.push_back("third"); };

    std::thread t3(&Foo::third, &foo, printThird);
    std::thread t2(&Foo::second, &foo, printSecond);
    std::thread t1(&Foo::first, &foo, printFirst);

    t1.join();
    t2.join();
    t3.join();

    assert(output.size() == 3);
    assert(output[0] == "first");
    assert(output[1] == "second");
    assert(output[2] == "third");

    std::cout << "Unit test passed!" << std::endl;
}

void runPerformanceTest() {
    const int NUM_ITERATIONS = 10000;
    std::atomic<int> counter(0);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        Foo foo;
        auto printFirst = [&counter]() { counter++; };
        auto printSecond = [&counter]() { counter++; };
        auto printThird = [&counter]() { counter++; };

        std::thread t3(&Foo::third, &foo, printThird);
        std::thread t2(&Foo::second, &foo, printSecond);
        std::thread t1(&Foo::first, &foo, printFirst);

        t1.join();
        t2.join();
        t3.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Performance test: " << duration.count() << "ms for "
              << NUM_ITERATIONS << " iterations" << std::endl;
    std::cout << "Total counter: " << counter << std::endl;
}

int main() {
    runUnitTest();
    runPerformanceTest();
    return 0;
}