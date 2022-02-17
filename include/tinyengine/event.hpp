#pragma once
#include "renderer.hpp"

void OnWindowResize(GLFWwindow* window, int width, int height);

bool IsKeyPressing(int key);

void InitEvent(const Size& windowInitSize);
bool IsLeftPressing();
bool IsRightPressing();
bool IsLeftPressed();
bool IsRightPressed();
Point GetMousePosition();
Point GetMousePositionMapped();

void EventUpdate();

void MouseBtnCallback(GLFWwindow* window, int button, int action, int mods);
