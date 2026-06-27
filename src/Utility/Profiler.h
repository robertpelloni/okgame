#pragma once
#include <string>
#include <chrono>
#include <unordered_map>

class Profiler {
public:
    static void beginBlock(const std::string& name);
    static void endBlock(const std::string& name);
    static void logResults();
    static void reset();

private:
    struct ProfileData {
        std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
        double totalMs = 0.0;
        int calls = 0;
    };
    static std::unordered_map<std::string, ProfileData> blocks;
};
