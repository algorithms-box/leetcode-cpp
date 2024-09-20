#include <cassert>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

class Foo {
  private:
    std::mutex mtx;
    std::condition_variable cv;
    int step = 0;

  public:
    Foo() {}

    void first() {
        std::unique_lock<std::mutex> lock(mtx);
        std::cout << "first";
        step = 1;
        cv.notify_all();
    }

    void second() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return step == 1; });
        std::cout << "second";
        step = 2;
        cv.notify_all();
    }

    void third() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return step == 2; });
        std::cout << "third";
    }
};

// Unit Testing
void testFoo() {
    Foo foo;
    std::thread t1(&Foo::first, &foo);
    std::thread t2(&Foo::second, &foo);
    std::thread t3(&Foo::third, &foo);

    t1.join();
    t2.join();
    t3.join();

    std::cout << "All tests passed.\n";
}

// Performance Testing
void performanceTest() {
    Foo foo;
    auto start = std::chrono::high_resolution_clock::now();
    std::thread t1(&Foo::first, &foo);
    std::thread t2(&Foo::second, &foo);
    std::thread t3(&Foo::third, &foo);

    t1.join();
    t2.join();
    t3.join();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Performance Test: " << elapsed.count() << " seconds\n";
}

int main() {
    testFoo();
    performanceTest();
    return 0;
}
