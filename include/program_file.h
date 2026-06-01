#pragma once

#include <string>

struct ProgramFile {
    std::string path;
    std::string executablePath;
    std::string outputPath;

    ProgramFile() {
        path = "";
        executablePath = "";
        outputPath = "";
    }

    ProgramFile(std::string path_, std::string executablePath_ = "", std::string outputPath_ = "") {
        path = path_;
        executablePath = executablePath_;
        outputPath = outputPath_;
    }
};