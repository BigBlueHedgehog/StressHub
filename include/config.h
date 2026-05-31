#pragma once

#include <string>
#include <program_file.h>


struct Config {
    ProgramFile gen;
    ProgramFile slow;
    ProgramFile fast;
    int testCnt = 0;

    Config() {
        gen = ProgramFile();
        slow = ProgramFile();
        fast = ProgramFile();
    }

    Config(std::string gen_, std::string slow_, std::string fast_, int testCnt_) {
        gen.path = gen_;
        slow.path = slow_;
        fast.path = fast_;
        testCnt = testCnt_;
    }
};

Config parseInput(int argc, char* argv[]);