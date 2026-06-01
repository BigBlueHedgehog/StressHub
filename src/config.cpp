#include "config.h"

#include <iostream>
#include <stdexcept>

Config parseInput(int argc, char* argv[]) {
    Config config;
    if (argc != 5) {
        throw std::runtime_error("Invalid count of arguments");
    }

    config.gen = ProgramFile(argv[1]);
    config.slow = ProgramFile(argv[2]);
    config.fast = ProgramFile(argv[3]);

    try {
        config.testCnt = std::stoi(argv[4]);
    } catch (...) {
        throw std::runtime_error("Invalid count of tests");
    }
    if (config.testCnt <= 0) {
        throw std::runtime_error("Invalid count of tests");
    }
    return config;
}