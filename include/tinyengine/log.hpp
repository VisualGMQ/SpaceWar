#pragma once

#include "pch.hpp"

#ifdef GAME_DEBUG
#define Log(msg, ...) do { \
    std::string filename(__FILE__); \
    filename = filename.substr(filename.find_last_of('/') + 1); \
    printf("[%s|%s: %d]\t" msg "\n", filename.c_str(), __func__, __LINE__, ## __VA_ARGS__); \
} while(0)
#else
#define Log(msg, ...)
#endif
