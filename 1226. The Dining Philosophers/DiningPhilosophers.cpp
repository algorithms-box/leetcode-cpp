#include "DiningPhilosophers.h"

DiningPhilosophers::DiningPhilosophers(int numPhilosophers)
    : forks(numPhilosophers) {}

DiningPhilosophers::~DiningPhilosophers() {}

void DiningPhilosophers::wantsToEat(int philosopher,
                                    std::function<void()> pickLeftFork,
                                    std::function<void()> pickRightFork,
                                    std::function<void()> eat,
                                    std::function<void()> putLeftFork,
                                    std::function<void()> putRightFork) {
    int leftFork = philosopher;
    int rightFork = (philosopher + 1) % forks.size();

    std::unique_lock<std::mutex> leftLock(forks[leftFork], std::defer_lock);
    std::unique_lock<std::mutex> rightLock(forks[rightFork], std::defer_lock);

    std::lock(leftLock, rightLock);

    pickLeftFork();
    pickRightFork();
    eat();
    putLeftFork();
    putRightFork();
}
