#include "LongestPushTime.h"

char Solution::slowestKey(const std::vector<int>& releaseTimes, const std::string& keysPressed) {
    int maxDuration = releaseTimes[0];
    char result = keysPressed[0];

    for (size_t i = 1; i < releaseTimes.size(); ++i) {
        int duration = releaseTimes[i] - releaseTimes[i - 1];
        if (duration > maxDuration || (duration == maxDuration && keysPressed[i] > result)) {
            maxDuration = duration;
            result = keysPressed[i];
        }
    }

    return result;
}