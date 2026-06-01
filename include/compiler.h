#pragma once

#include <string>

#include "config.h"
#include "program_file.h"

bool compileFile(const ProgramFile& file);

bool compileAll(const Config& config);