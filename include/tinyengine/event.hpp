#pragma once
#include "renderer.hpp"

void OnWindowResize(GLFWwindow* window, int width, int height);

bool IsKeyPressing(int key);

bool IsLeftPressing();
bool IsRightPressing();
Point GetMousePosition();
