#include <cassert>
#include <chrono>
#include <iostream>
#include <list>
#include <unordered_map>

class LRUCache {
  private:
    int capacity;
    std::list<std::pair<int, int>> items;
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> cache;

  public:
    LRUCache(int capacity) : capacity(capacity) {}

    int get(int key) {
        auto it = cache.find(key);
        if (it == cache.end()) {
            return -1;
        }
        // Move the item to the front
        items.splice(items.begin(), items, it->second);
        return it->second->second;
    }

    void put(int key, int value) {
        auto it = cache.find(key);
        if (it != cache.end()) {
            // Update the value and move the item to the front
            it->second->second = value;
            items.splice(items.begin(), items, it->second);
        } else {
            if (items.size() == capacity) {
                // Remove the last item
                cache.erase(items.back().first);
                items.pop_back();
            }
            // Insert the new item at the front
            items.emplace_front(key, value);
            cache[key] = items.begin();
        }
    }
};

// 单元测试
void test() {
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    assert(cache.get(1) == 1);
    cache.put(3, 3); // evicts key 2
    assert(cache.get(2) == -1);
    cache.put(4, 4); // evicts key 1
    assert(cache.get(1) == -1);
    assert(cache.get(3) == 3);
    assert(cache.get(4) == 4);
    std::cout << "All tests passed!" << std::endl;
}

// 性能测试
void performanceTest() {
    LRUCache cache(1000);
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; ++i) {
        cache.put(i, i);
        int val = cache.get(i);
        (void)val; // Avoid unused variable warning
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "Performance test completed in " << elapsed.count() << " ms"
              << std::endl;
}

int main() {
    test();            // Run unit tests
    performanceTest(); // Run performance test
    return 0;
}