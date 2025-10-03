#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
using namespace std;

class TimeUtils {
public:
    static string getCurrentTime() {
        // get current system time
        auto now = chrono::system_clock::now();
        time_t currentTime = chrono::system_clock::to_time_t(now);

        // convert to string
        string timeStr = ctime(&currentTime);

        // remove trailing newline that ctime() adds
        if (!timeStr.empty() && timeStr.back() == '\n') {
            timeStr.pop_back();
        }

        return timeStr;
    }
};

#endif

