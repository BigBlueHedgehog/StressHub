#include "config.h"

#include <ctime>
#include <iostream>
#include <stdexcept>

Config parseInput(int argc, char* argv[]) {
    Config config;
    if (argc < 5) {
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

    for (int i = 5; i < argc; ++i) {
        if (std::string(argv[i]) == "--seed") {
            if (i + 1 >= argc) {
                throw std::runtime_error("Invalid seed");
            }
            config.seed = std::stoi(argv[i + 1]);
            config.isSeed = true;
            i++;
        } else {
            throw std::runtime_error("Invalid argument " + std::string(argv[i]));
        }
    }

    if (!config.isSeed) {
        config.seed = time(0);
    }
    return config;
}