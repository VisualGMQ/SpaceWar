#pragma once

#ifdef TINYENGINE_USE_GLEW
    #include "GL/glew.h"
#else
    #include "glad/gl.h"
#endif

#include "GLFW/glfw3.h"

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <memory>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <random>
#include <cmath>
#include <type_traits>
#include <initializer_list>
#include <algorithm>
#include <stack>
#include <utility>
#include <limits>
#include <cassert>

#include "miniaudio.h"
#include "stb_image.h"

#ifdef USE_GLM
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#endif
