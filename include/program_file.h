#pragma once

#include <string>


struct ProgramFile {
    std::string path = "";
    std::string executablePath = "";

    ProgramFile() {
        path = "";
        executablePath = "";
    }

    ProgramFile(std::string path_, std::string executablePath_ = "") {
        path = path_;
        executablePath = executablePath_;
    }
};