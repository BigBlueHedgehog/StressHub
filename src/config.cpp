#include <config.h>

#include <iostream>

Config parseInput(int argc, char* argv[]) {
    Config config;
    config.gen = ProgramFile(argv[1]);
    config.slow = ProgramFile(argv[2]);
    config.fast = ProgramFile(argv[3]);

    try {
        config.testCnt = std::stoi(argv[4]);
    } catch (...) {
        std::cerr << "Invalid countOfTests: " << argv[4] << '\n';
        return config;
    }
    if (config.testCnt <= 0) {
        std::cerr << "Invalid countOfTests: " << config.testCnt << '\n';
        return config;
    }
    return config;
}