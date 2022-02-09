#include "tinyengine/renderer.hpp"
#include "tinyengine/engine.hpp"

Color Renderer::color_ = {255, 255, 255, 255};

struct {
    GLuint vbo;
    GLuint vao;

    Unique<Shader> shader;

    Unique<Texture> WhiteTexture;
    Camera* camera = nullptr;

    const std::array<Vertex, 6> vertices = {
        Vertex{-0.5f, 0.5f, 0.0f, 1.0f},
        Vertex{ 0.5f,-0.5f, 1.0f, 0.0f},
        Vertex{-0.5f,-0.5f, 0.0f, 0.0f},

        Vertex{-0.5f, 0.5f, 0.0f, 1.0f},
        Vertex{ 0.5f, 0.5f, 1.0f, 1.0f},
        Vertex{ 0.5f,-0.5f, 1.0f, 0.0f}
    };
} Context;

void createWhiteTexture() {
    unsigned char white[] = {0xFF, 0xFF, 0xFF};
    Context.WhiteTexture.reset(new Texture(white,
                                           1, 1,
                                           GL_RGB));
}

void initRenderContext() {
    GL_CALL(glGenVertexArrays(1, &Context.vao));
    GL_CALL(glGenBuffers(1, &Context.vbo));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, Context.vbo));
    GL_CALL(glBindVertexArray(Context.vao));
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0,
                                  4,
                                  GL_FLOAT,
                                  GL_FALSE,
                                  4 * sizeof(GLfloat),
                                  (void*)0));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CALL(glBindVertexArray(0));
}

void initShader(const std::string& vertex, const std::string& fragment) {
    std::ifstream file(vertex);
    if (file.fail()) {
        Log("vertex shader %s load failed", vertex.c_str());
        FATAL_ERROR("vertex shader load failed");
    }
    std::string vertexCode((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());

    file.close();
    file.open(fragment);
    if (file.fail()) {
        Log("fragment shader %s load failed", fragment.c_str());
        FATAL_ERROR("fragment shader load failed");
    }
    std::string fragmentCode((std::istreambuf_iterator<char>(file)),
                              std::istreambuf_iterator<char>());
    file.close();

    Context.shader.reset(new Shader(vertexCode, fragmentCode));
}

void setShaderOrtho() {
    auto size = engine.GetWindowSize();
    Context.shader->SetMat4("ortho",
                            CreateOrthoMat(0.0f, size.x,
                                           size.y, 0.0f,
                                           -1.0f, 1.0f));
}

void Renderer::Init() {
    GL_CALL(glEnable(GL_BLEND));
    GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    createWhiteTexture();
    initRenderContext();
    initShader("assets/shaders/vertex.shader",
               "assets/shaders/fragment.shader");
    setShaderOrtho();
}

void Renderer::SetClearColor(const Color& color) {
    GL_CALL(glClearColor(color.r, color.g, color.b, color.a));
}

void Renderer::DrawLine(const Point& p1, const Point& p2) {
    Vertex vertices[] = {
        {p1.x, p1.y,  0, 0},
        {p2.x, p2.y,  0, 0}
    };
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, Context.vbo));
    GL_CALL(glBindVertexArray(Context.vao));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    Context.WhiteTexture->Bind();
    Context.shader->Use();
    Context.shader->SetMat4("model", Mat44::Eye);
    GL_CALL(glDrawArrays(GL_LINES, 0, 2));
}

void Renderer::DrawRect(const Rect& rect) {
    Vertex vertices[] = {
        {rect.x,          rect.y,            0, 0},
        {rect.x + rect.w, rect.y,            0, 0},
        {rect.x + rect.w, rect.y + rect.h,   0, 0},
        {rect.x,          rect.y + rect.h,   0, 0}
    };
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, Context.vbo));
    GL_CALL(glBindVertexArray(Context.vao));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    Context.WhiteTexture->Bind();
    Context.shader->Use();
    Context.shader->SetMat4("model", Mat44::Eye);
    GL_CALL(glDrawArrays(GL_LINE_LOOP, 0, 4));
}

void Renderer::FillRect(const Rect& rect) {
    drawRectFrag(nullptr,
                 Context.vertices,
                 CreateSRT(Point{rect.x + rect.w / 2, rect.y + rect.h / 2},
                           Point{rect.w, rect.h},
                           0),
                 Renderer::color_);
}

void Renderer::DrawTile(const Tile& tile,
                        const Point& pos,
                        const Size& size,
                        float degree,
                        Renderer::FlipFlag flip) {
    if (size.w == 0 && size.h == 0) {
        DrawTexture(tile.texture, &tile.rect, pos, tile.size, degree, flip);
    } else {
        DrawTexture(tile.texture, &tile.rect, pos, size, degree, flip);
    }
}

void Renderer::DrawTexture(const Texture* texture,
                           const Rect* srcrect,
                           const Point& pos,
                           const Size& size,
                           float degree,
                           FlipFlag flip) {
    if (texture) {
        auto scale = size;
        if (size.w == 0 && size.h == 0) {
            scale = texture->GetSize();
        }
        if (flip & Vertical) {
            scale.h *= -1;
        }
        if (flip & Horizontal) {
            scale.w *= -1;
        }
        DrawTexture(texture, srcrect, CreateSRT(pos, scale, degree));
    }
}

void Renderer::DrawTexture(const Texture* texture,
                           const Rect* rect,
                           const Mat44& transform,
                           const Color& color) {
    if (!texture) return;
    auto& size = texture->GetSize();
    if (!rect) {
        drawRectFrag(texture, Context.vertices, transform, color);
    } else {
        auto vertices = Context.vertices;
        vertices[0].texcoord = Point{rect->x / size.w,
                                     (rect->y + rect->h) / size.h};
        vertices[1].texcoord = Point{(rect->x + rect->w) / size.w,
                                      rect->y / size.h};
        vertices[2].texcoord = Point{rect->x / size.w, rect->y / size.h};
        vertices[3].texcoord = vertices[0].texcoord;
        vertices[4].texcoord = Point{(rect->x + rect->w) / size.w,
                                     (rect->y + rect->h) / size.h};
        vertices[5].texcoord = vertices[1].texcoord;
        drawRectFrag(texture, vertices, transform, color);
    }
}

void Renderer::drawRectFrag(const Texture* texture,
                            const std::array<Vertex, 6>& vertices,
                            const Mat44& transform,
                            const Color& color) {
    Context.shader->Use();
    Context.shader->SetInt("Texture", 0);
    if (texture) {
        texture->Bind(0);
    } else {
        Context.WhiteTexture->Bind(0);
    }

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, Context.vbo));
    GL_CALL(glBindVertexArray(Context.vao));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER,
                         sizeof(Vertex) * vertices.size(),
                         vertices.data(),
                         GL_STATIC_DRAW));

    Renderer::SetDrawColor(color);
    Context.shader->SetMat4("model", transform);
    GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 6));

}

void Renderer::Clear() {
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT));
}

void Renderer::SetDrawColor(const Color& color) {
    color_ = color;
    Context.shader->SetFloat4("aColor", color.r, color.g, color.b, color.a);
}

const Color& Renderer::GetDrawColor() {
    return color_;
}

void Renderer::SetViewport(int x, int y, int w, int h) {
    GL_CALL(glViewport(x, y, w, h));
}

void Renderer::SetCamera(Camera& camera) {
    Context.camera = &camera;
    Context.camera->TryCalcView();
    Context.shader->SetMat4("view", Context.camera->GetView());
}

void Renderer::Shutdown() {
    Context.WhiteTexture.reset();
    GL_CALL(glDeleteBuffers(1, &Context.vbo));
    GL_CALL(glDeleteVertexArrays(1, &Context.vao));
    Context.shader.reset();
}
