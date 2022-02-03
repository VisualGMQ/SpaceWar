#include "texture.hpp"

Texture::Texture(const std::string& filename) {
    int w, h, channels;
    unsigned char* data = stbi_load(filename.c_str(), &w, &h, &channels, 0);
    if (channels == 4) {
        format_ = GL_RGBA;
    }else if (channels == 3) {
        format_ = GL_RGB;
    }
    size_.x = w;
    size_.y = h;

    createFromPixels(data, w, h, format_);

    stbi_image_free(data);
}

Texture::Texture(const unsigned char* data, int w, int h, GLenum format) {
    createFromPixels(data, w, h, format);
}

void Texture::createFromPixels(const unsigned char* data, int w, int h, GLenum format) {
    size_.x = w;
    size_.y = h;
    format_ = format;
    GL_CALL(glGenTextures(1, &texture_));
    Bind();
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GL_CALL(glTexImage2D(GL_TEXTURE_2D,
                         0,
                         GL_RGBA,
                         w, h,
                         0,
                         format_,
                         GL_UNSIGNED_BYTE,
                         data));
    if (size_.x == size_.y) {
        GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));
    }
    Unbind();
}

void Texture::Bind(GLuint slot) const {
    GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, texture_));
}

void Texture::Unbind() const {
    GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}

Texture::~Texture() {
    GL_CALL(glDeleteTextures(1, &texture_));
}
