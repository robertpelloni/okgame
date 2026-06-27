#include "stdafx.h"
#include "Profiler.h"
#include "Logger.h"

std::unordered_map<std::string, Profiler::ProfileData> Profiler::blocks;

void Profiler::beginBlock(const std::string& name) {
    blocks[name].startTime = std::chrono::high_resolution_clock::now();
}

void Profiler::endBlock(const std::string& name) {
    auto endTime = std::chrono::high_resolution_clock::now();
    auto& data = blocks[name];
    std::chrono::duration<double, std::milli> duration = endTime - data.startTime;
    data.totalMs += duration.count();
    data.calls++;
}

void Profiler::logResults() {
    Main::log.info("--- Performance Profiler Results ---");
    for (const auto& pair : blocks) {
        double avg = pair.second.calls > 0 ? pair.second.totalMs / pair.second.calls : 0;
        Main::log.info(pair.first + ": Total=" + std::to_string(pair.second.totalMs) + "ms, Calls=" + std::to_string(pair.second.calls) + ", Avg=" + std::to_string(avg) + "ms");
    }
}

void Profiler::reset() {
    blocks.clear();
}
