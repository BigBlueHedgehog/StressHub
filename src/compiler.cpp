#include "compiler.h"

#include <iostream>

bool compileFile(const ProgramFile& file) {
    std::string command = "g++ " + file.path + " -o " + file.executablePath;
    int code = system(command.c_str());
    if (code != 0) {
        std::cerr << "Compilation failed: " << file.path << '\n';
        return false;
    }
    return true;
}

bool compileAll(const Config& config) {
    if (!compileFile(config.gen)) return false;
    if (!compileFile(config.slow)) return false;
    if (!compileFile(config.fast)) return false;
    return true;
}