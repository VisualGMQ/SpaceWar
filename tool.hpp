#pragma once
#include "pch.hpp"

template <typename T>
using Unique = std::unique_ptr<T>;

template <typename T>
using Ref = std::shared_ptr<T>;
