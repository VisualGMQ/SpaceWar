#pragma once

#include "pch.hpp"

#define Log(msg, ...) printf("[%s: %d] " msg, __func__, __LINE__, ## __VA_ARGS__)
