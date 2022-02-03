#include "shader.hpp"

GLuint createShader(const std::string& code, GLenum type) {
    GLuint shader;
    GL_CALL(shader = glCreateShader(type));
    if (shader == 0) {
        Log("create shader failed");
    }
    const GLchar* const sources[] = {code.c_str()};
    GL_CALL(glShaderSource(shader, 1, sources, nullptr));
    GL_CALL(glCompileShader(shader));
    GLint err;
    GL_CALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &err));
    if (err == GL_FALSE) {
        char buf[1024] = {0};
        GL_CALL(glGetShaderInfoLog(shader, sizeof(buf), nullptr, buf));
        Log("shader compile failed:\n%s", buf);
    }
    return shader;
}

Shader::Shader(const std::string& vertex,
               const std::string& fragment) {
    GLuint vertexShader = createShader(vertex, GL_VERTEX_SHADER),
           fragmentShader = createShader(fragment, GL_FRAGMENT_SHADER);

    GL_CALL(program_ = glCreateProgram());
    if (program_ == 0) {
        Log("create shader program failed");
    } else {
        GL_CALL(glAttachShader(program_, vertexShader));
        GL_CALL(glAttachShader(program_, fragmentShader));
        GL_CALL(glLinkProgram(program_));
        GLint err;
        GL_CALL(glGetProgramiv(program_, GL_LINK_STATUS, &err));
        if (err == GL_FALSE) {
            char buf[1024] = {0};
            GL_CALL(glGetProgramInfoLog(program_, sizeof(buf), nullptr, buf));
            Log("link shader program failed:\n%s", buf);
        }
    }
}

Shader::~Shader() {
    GL_CALL(glDeleteProgram(program_));
}

void Shader::SetInt(const std::string& name, int i) {
    GLint loc;
    GL_CALL(loc = glGetUniformLocation(program_, name.c_str()));
    if (loc == -1) {
        Log("uniform variable %s is not found", name.c_str());
    } else {
        Use();
        GL_CALL(glUniform1i(loc, i));
    }
}

void Shader::SetInt2(const std::string& name, int i1, int i2) {
    GLint loc;
    GL_CALL(loc = glGetUniformLocation(program_, name.c_str()));
    if (loc == -1) {
        Log("uniform variable %s is not found", name.c_str());
    } else {
        Use();
        GL_CALL(glUniform2i(loc, i1, i2));
    }
}

void Shader::SetInt3(const std::string& name, int i1, int i2, int i3) {
    GLint loc;
    GL_CALL(loc = glGetUniformLocation(program_, name.c_str()));
    if (loc == -1) {
        Log("uniform variable %s is not found", name.c_str());
    } else {
        Use();
        GL_CALL(glUniform3i(loc, i1, i2, i3));
    }
}

void Shader::SetInt4(const std::string& name, int i1, int i2, int i3, int i4) {
    GLint loc;
    GL_CALL(loc = glGetUniformLocation(program_, name.c_str()));
    if (loc == -1) {
        Log("uniform variable %s is not found", name.c_str());
    } else {
        Use();
        GL_CALL(glUniform4i(loc, i1, i2, i3, i4));
    }
}

void Shader::SetFloat(const std::string& name, float f) {
    GLint loc;
    GL_CALL(loc = glGetUniformLocation(program_, name.c_str()));
    if (loc == -1) {
        Log("uniform variable %s is not found", name.c_str());
    } else {
        Use();
        GL_CALL(glUniform1f(loc, f));
    }
}

void Shader::SetFloat2(const std::string& name, float f1, float f2) {
    GLint loc;
    GL_CALL(loc = glGetUniformLocation(program_, name.c_str()));
    if (loc == -1) {
        Log("uniform variable %s is not found", name.c_str());
    } else {
        Use();
        GL_CALL(glUniform2f(loc, f1, f2));
    }
}

void Shader::SetFloat3(const std::string& name, float f1, float f2, float f3) {
    GLint loc;
    GL_CALL(loc = glGetUniformLocation(program_, name.c_str()));
    if (loc == -1) {
        Log("uniform variable %s is not found", name.c_str());
    } else {
        Use();
        GL_CALL(glUniform3f(loc, f1, f2, f3));
    }
}

void Shader::SetFloat4(const std::string& name, float f1, float f2, float f3, float f4) {
    GLint loc;
    GL_CALL(loc = glGetUniformLocation(program_, name.c_str()));
    if (loc == -1) {
        Log("uniform variable %s is not found", name.c_str());
    } else {
        Use();
        GL_CALL(glUniform4f(loc, f1, f2, f3, f4));
    }
}

void Shader::SetMat4(const std::string& name, const Mat44& mat) {
    GLint loc;
    GL_CALL(loc = glGetUniformLocation(program_, name.c_str()));
    if (loc == -1) {
        Log("uniform variable %s is not found", name.c_str());
    } else {
        Use();
        GL_CALL(glUniformMatrix4fv(loc, 1, GL_FALSE, mat.Data()));
    }
}

#ifdef USE_GLM
void Shader::SetMat4(const std::string& name, const glm::mat4& mat) {
    GLint loc;
    GL_CALL(loc = glGetUniformLocation(program_, name.c_str()));
    if (loc == -1) {
        Log("uniform variable %s is not found", name.c_str());
    } else {
        Use();
        GL_CALL(glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat)));
    }
}
#endif
