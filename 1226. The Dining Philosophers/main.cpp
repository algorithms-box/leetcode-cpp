#include "DiningPhilosophers.h"
#include <cassert>
#include <chrono>
#include <functional>
#include <iostream>

void pickFork(int philosopher, std::vector<std::mutex> &forks, int fork) {
    std::cout << "Philosopher " << philosopher << " picked fork " << fork
              << ".\n";
    forks[fork].lock();
}

void putFork(int philosopher, std::vector<std::mutex> &forks, int fork) {
    std::cout << "Philosopher " << philosopher << " put fork " << fork
              << " down.\n";
    forks[fork].unlock();
}

void eat(int philosopher) {
    std::cout << "Philosopher " << philosopher << " is eating.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void testDiningPhilosophers() {
    const int numPhilosophers = 5;
    DiningPhilosophers dp(numPhilosophers);
    std::vector<std::thread> philosophers;

    for (int i = 0; i < numPhilosophers; ++i) {
        philosophers.emplace_back([&dp, i] {
            dp.wantsToEat(i, std::bind(pickFork, i, std::ref(dp.forks), i),
                          std::bind(pickFork, i, std::ref(dp.forks),
                                    (i + 1) % numPhilosophers),
                          std::bind(eat, i),
                          std::bind(putFork, i, std::ref(dp.forks), i),
                          std::bind(putFork, i, std::ref(dp.forks),
                                    (i + 1) % numPhilosophers));
        });
    }

    for (auto &philosopher : philosophers) {
        philosopher.join();
    }
}

int main() {
    testDiningPhilosophers();
    return 0;
}