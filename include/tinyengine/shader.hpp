#pragma once
#include "pch.hpp"
#include "glhelpfunc.hpp"
#include "log.hpp"
#include "tool.hpp"
#include "libmath.hpp"

class Shader final {
public:
    Shader(const std::string& vertex,
           const std::string& fragment);
    Shader(const Shader&) = delete;
    ~Shader();
    Shader& operator=(const Shader&) = delete;

    inline bool Valid() const { return program_ != 0; }
    GLuint Get() const { return program_; }

    void SetInt(const std::string& name, int i);
    void SetInt2(const std::string& name, int i1, int i2);
    void SetInt3(const std::string& name, int i1, int i2, int i3);
    void SetInt4(const std::string& name, int i1, int i2, int i3, int i4);
    void SetFloat(const std::string& name, float f);
    void SetFloat2(const std::string& name, float f1, float f2);
    void SetFloat3(const std::string& name, float f1, float f2, float f3);
    void SetFloat4(const std::string& name, float f1, float f2, float f3, float f4);
    void SetMat4(const std::string& name, const Mat44& mat);

#ifdef USE_GLM
    void SetMat4(const std::string& name, const glm::mat4& mat);
#endif

    inline void Use() const { GL_CALL(glUseProgram(program_)); }

private:
    GLuint program_;
};
