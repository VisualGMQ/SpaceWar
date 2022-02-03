#pragma once
#include "pch.hpp"
#include "libmath.hpp"
#include "glhelpfunc.hpp"
#include "tool.hpp"

class Texture {
public:
    Texture(const std::string& filename);
    Texture(const unsigned char* data, int w, int h, GLenum format);
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    ~Texture();

    void Bind(GLuint slot = 0) const;
    void Unbind() const;

    const Size& GetSize() const { return size_; }

private:
    GLuint texture_;
    GLenum format_;
    Size size_;

    void createFromPixels(const unsigned char* data, int w, int h, GLenum format);
};

