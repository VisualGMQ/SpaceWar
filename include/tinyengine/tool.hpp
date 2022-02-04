#pragma once

#include "pch.hpp"

template <typename T>
using Unique = std::unique_ptr<T>;

template <typename T>
using Ref = std::shared_ptr<T>;

#ifdef GAME_DEBUG
#define FATAL_ERROR(msg) assert((void(msg), false))
#else
#define FATAL_ERROR(msg)
#endif
