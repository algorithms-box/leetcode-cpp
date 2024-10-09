#include <cassert>
#include <chrono>
#include <iostream>
#include <list>
#include <random>
#include <unordered_map>

class LRUCache {
  private:
    std::size_t capacity;
    std::list<std::pair<int, int>> cache;
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> map;

  public:
    LRUCache(int capacity) : capacity(static_cast<std::size_t>(capacity)) {}

    int get(int key) {
        auto it = map.find(key);
        if (it == map.end()) {
            return -1;
        }
        cache.splice(cache.begin(), cache, it->second);
        return it->second->second;
    }

    void put(int key, int value) {
        auto it = map.find(key);
        if (it != map.end()) {
            it->second->second = value;
            cache.splice(cache.begin(), cache, it->second);
        } else {
            if (cache.size() == capacity) {
                map.erase(cache.back().first);
                cache.pop_back();
            }
            cache.emplace_front(key, value);
            map[key] = cache.begin();
        }
    }
};

void runUnitTests() {
    // Test case 1
    LRUCache lRUCache(2);
    lRUCache.put(1, 1);
    lRUCache.put(2, 2);
    assert(lRUCache.get(1) == 1);
    lRUCache.put(3, 3);
    assert(lRUCache.get(2) == -1);
    lRUCache.put(4, 4);
    assert(lRUCache.get(1) == -1);
    assert(lRUCache.get(3) == 3);
    assert(lRUCache.get(4) == 4);

    // Test case 2
    LRUCache cache(2);
    cache.put(2, 1);
    cache.put(1, 1);
    cache.put(2, 3);
    cache.put(4, 1);
    assert(cache.get(1) == -1);
    assert(cache.get(2) == 3);

    std::cout << "All unit tests passed!" << std::endl;
}

void runPerformanceTest() {
    const int CAPACITY = 10000;
    const int NUM_OPERATIONS = 1000000;

    LRUCache cache(CAPACITY);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> key_dis(1, CAPACITY * 2);
    std::uniform_int_distribution<> value_dis(1, 10000);
    std::uniform_int_distribution<> op_dis(0, 1);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        if (op_dis(gen) == 0) { // get operation
            cache.get(key_dis(gen));
        } else { // put operation
            cache.put(key_dis(gen), value_dis(gen));
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Performance test: " << duration.count() << "ms for "
              << NUM_OPERATIONS << " operations" << std::endl;
}

int main() {
    runUnitTests();
    runPerformanceTest();
    return 0;
}