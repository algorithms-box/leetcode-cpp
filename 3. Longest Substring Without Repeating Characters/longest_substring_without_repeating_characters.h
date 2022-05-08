#include <string>
using std::string;
#include <unordered_map>
using std::unordered_map;
#include <algorithm>
using std::max;

class Solution {
  public:
    int lengthOfLongestSubstring(string s) {
        if (s.size() <= 1) {
            return s.size();
        }
        int max_length = 0;
        unordered_map<char, int> tmpMap;
        for (int left_cursor = 0; left_cursor < s.size(); left_cursor++) {
            tmpMap.clear();
            for (int right_cursor = 0; right_cursor < s.size(); right_cursor++) {
                if (right_cursor >= left_cursor) {
                    /* Note, if the substring without repeating chars is end with tail, */
                    /* then we need take care of that] */
                    auto found = tmpMap.find(s[right_cursor]);
                    if (found != tmpMap.end() || right_cursor == s.size()) {
                        break;
                    }
                    tmpMap[s[right_cursor]] = right_cursor;
                }
            }
            max_length = max(max_length, tmpMap.size());
        }
        return max_length;
    }

  private:
    int max(int x, int y) {
        if (x > y) {
            return x;
        }
        return y;
    }

  private:
    void printMap(unordered_map<char, int> t_map) {
        for (auto kv : t_map) {
            std::cout << kv.first << ":" << kv.second << "->";
        }
        std::cout << "\b\b" << std::endl;
    }

};
