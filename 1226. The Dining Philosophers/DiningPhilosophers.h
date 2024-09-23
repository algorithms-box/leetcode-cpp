#ifndef DINING_PHILOSOPHERS_H
#define DINING_PHILOSOPHERS_H

#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class DiningPhilosophers {
  public:
    explicit DiningPhilosophers(int numPhilosophers);
    ~DiningPhilosophers();

    void wantsToEat(int philosopher, std::function<void()> pickLeftFork,
                    std::function<void()> pickRightFork,
                    std::function<void()> eat,
                    std::function<void()> putLeftFork,
                    std::function<void()> putRightFork);

  private:
    std::vector<std::mutex> forks;
};

#endif // DINING_PHILOSOPHERS_H
