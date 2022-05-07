#include <string>
using std::string;
#include <unordered_map>
using std::unordered_map;
#include <algorithm>
using std::max;

class Solution {
  public:
    int lengthOfLongestSubstring(string s) {
        int start_cursor = -1;
        int max_length = 0;
        unordered_map<char, int> tmpMap;

        for(int i =0; i<s.size(); i++) {
            auto found = tmpMap.find(s[i]);
            if(found != tmpMap.end() && found->second > start_cursor) {
                // print the string without repeating chars for now
                /* printMap(tmpMap); */
                // let start_cursor move to char ch last one position before this loop
                start_cursor = tmpMap[s[i]];
                tmpMap[s[i]] = i;

            } else {
                tmpMap[s[i]] = i;
                max_length = max(max_length, i - start_cursor);
            }

        }
        return max_length;
    }

  private:
    void printMap(unordered_map<char, int> t_map) {
        for( auto kv:t_map) {
            std::cout << kv.first << ":" << kv.second << "->";
        }
        std::cout << "\b\b" << std::endl;
    }
};
