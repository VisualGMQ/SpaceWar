#include "renderer.hpp"

struct RenderContext {

};

void Renderer::Init() {
    if (!gladLoadGL(glfwGetProcAddress)) {
        glfwTerminate();
        throw std::runtime_error("glad load failed");
    }

    GL_CALL(glEnable(GL_DEPTH_TEST));
    GL_CALL(glEnable(GL_STENCIL_TEST));
}

void Renderer::SetClearColor(const Color& color) {
    GL_CALL(glClearColor(color.r, color.g, color.b, color.a));
}

void Renderer::DrawLine(const Point& p1, const Point& p2) {
}

void Renderer::DrawRect(const Rect& rect) {
}

void Renderer::FillRect(const Rect& rect) {
}

void Renderer::SetDrawColor(const Color& color) {
}

void Renderer::Clear() {
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT));
}

void Renderer::SetViewport(int x, int y, int w, int h) {
    GL_CALL(glViewport(x, y, w, h));
}

void Renderer::Shutdown() {}
