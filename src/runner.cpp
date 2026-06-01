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

bool runGenFile(const ProgramFile &file, const std::string &inputFile) {
    std::string command = "./" + file.executablePath + " > " + inputFile;
    int code = system(command.c_str());
    if (code != 0) {
        std::cerr << "Runtime failed: " << file.path << '\n';
        return false;
    }
    return true;
}

bool runAll(const Config &config, const std::string &inputFile) {
    if (!runGenFile(config.gen, inputFile)) return false;
    if (!runFile(config.slow, inputFile)) return false;
    if (!runFile(config.fast, inputFile)) return false;
    return true;
}