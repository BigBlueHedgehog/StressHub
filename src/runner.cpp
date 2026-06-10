#include "runner.h"

#include <iostream>

bool runFile(const ProgramFile &file, const std::string &inputFile) {
    std::string command = "./" + file.executablePath + " < " + inputFile + " > " + file.outputPath;
    int code = system(command.c_str());
    if (code != 0) {
        std::cerr << "Runtime failed: " << file.path << '\n';
        return false;
    }
    return true;
}

bool runGenFile(const ProgramFile &file, const std::string &inputFile, int seed, int test_number) {
    std::string command = "./" + file.executablePath + " " + std::to_string(seed) + " " +
                          std::to_string(test_number) + " > " + inputFile;
    int code = system(command.c_str());
    if (code != 0) {
        std::cerr << "Runtime failed: " << file.path << '\n';
        return false;
    }
    return true;
}

bool runAll(const Config &config, const std::string &inputFile, int test_number) {
    if (!runGenFile(config.gen, inputFile, config.seed, test_number)) return false;
    if (!runFile(config.slow, inputFile)) return false;
    if (!runFile(config.fast, inputFile)) return false;
    return true;
}