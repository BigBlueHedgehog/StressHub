#include <runner.h>
#include <iostream>


bool runFile(const ProgramFile& file, const std::string &outputFile,
             const std::string &inputFile) {
    std::string command = "./" + file.executablePath + " < " + inputFile + " > " + outputFile;
    int code = system(command.c_str());
    if (code != 0) {
        std::cerr << "Runtime failed: " << file.path << '\n';
        return false;
    }
    return true;
}

bool runGenFile(const ProgramFile& file,
                const std::string &inputFile) {
    std::string command = "./" + file.executablePath + " > " + inputFile;
    int code = system(command.c_str());
    if (code != 0) {
        std::cerr << "Runtime failed: " << file.path << '\n';
        return false;
    }
    return true;
}