#include "shader.hpp"

SourceCode::SourceCode(const std::string& code)
    : code_(code) {}

Shader::ShaderStruct::ShaderStruct(const SourceCode& code, Shader::ShaderStruct::Type type) {
    if (code.Empty()) { return; }
    switch (type) {
        case ShaderStruct::Vertex:
            Log("compiling vertex shader ...");
            GL_CALL(shader_ = glCreateShader(GL_VERTEX_SHADER));
            break;
        case Fragment:
            Log("compiling fragment shader ...");
            GL_CALL(shader_ = glCreateShader(GL_FRAGMENT_SHADER));
            break;
        case Geometry:
            Log("compiling geometry shader ...");
            GL_CALL(shader_ = glCreateShader(GL_GEOMETRY_SHADER));
            break;
    }
    if (shader_ == 0) {
        Log("create shader failed");
    } else {
        const GLchar* const sources[] = {code.GetCode().c_str()};
        GL_CALL(glShaderSource(shader_, 1, sources, nullptr));
        GL_CALL(glCompileShader(shader_));
        GLint err;
        GL_CALL(glGetShaderiv(shader_, GL_COMPILE_STATUS, &err));
        if (err == GL_FALSE) {
            char buf[1024] = {0};
            GL_CALL(glGetShaderInfoLog(shader_, sizeof(buf), nullptr, buf));
            Log("shader compile failed:\n%s", buf);
        }
    }
}

Shader::ShaderStruct::~ShaderStruct() {
    GL_CALL(glDeleteShader(shader_));
}

Shader::Shader(const SourceCode* vertex,
               const SourceCode* fragment,
               const SourceCode* geometry) {
    if (vertex) {
        shaders_[0].reset(new ShaderStruct(*vertex, ShaderStruct::Vertex));
    }
    if (fragment) {
        shaders_[1].reset(new ShaderStruct(*fragment, ShaderStruct::Fragment));
    }
    if (geometry) {
        shaders_[2].reset(new ShaderStruct(*geometry, ShaderStruct::Geometry));
    }

    GL_CALL(program_ = glCreateProgram());
    if (program_ == 0) {
        Log("create shader program failed");
    } else {
        for (const auto& shader : shaders_) {
            if (shader) {
                GL_CALL(glAttachShader(program_, shader->Get()));
            }
        }
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
    for (auto& shader : shaders_)
        shader.reset();
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

// void Shader::SetMat4(const std::string& name, const glm::mat4& mat, bool transpose) {
//     GLint loc;
//     GL_CALL(loc = glGetUniformLocation(program_, name.c_str()));
//     if (loc == -1) {
//         Log("uniform variable %s is not found", name.c_str());
//     } else {
//         Use();
//         GL_CALL(glUniformMatrix4fv(loc, 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(mat)));
//     }
// }

// void Shader::SetFloatVec3(const std::string& name, const glm::vec3& data) {
//     GLint loc;
//     GL_CALL(loc = glGetUniformLocation(program_, name.c_str()));
//     if (loc == -1) {
//         Log("uniform variable %s is not found", name.c_str());
//     } else {
//         Use();
//         GL_CALL(glUniform3fv(loc, 1, glm::value_ptr(data)));
//     }
// }


SourceCodePtr CreateSourceCodeFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.fail()) {
        Log("SourceCodeRes %s load failed", filename.c_str());
        return nullptr;
    }
    std::string code((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());
    return CreateSourceCode(code);
}

void parseShaderFile(const std::string& code,
                             std::string& vertexCode,
                             std::string& geometryCode,
                             std::string& fragmentCode) {
    std::string::size_type pos[3] = {code.find("#type vertex"),
                                     code.find("#type geometry"),
                                     code.find("#type fragment")};
    /* 1 - vertex shader code
       2 - tessellation shader code
       3 - fragment shader code */
    std::string* codes[3] = {&vertexCode,
                             &geometryCode,
                             &fragmentCode};

    // sort three code by their position
    if (pos[0] > pos[1]) {
        std::swap(pos[0], pos[1]);
        std::swap(codes[0], codes[1]);
    }
    if (pos[1] > pos[2]) {
        std::swap(pos[1], pos[2]);
        std::swap(codes[1], codes[2]);
    }
    if (pos[0] > pos[1]) {
        std::swap(pos[0], pos[1]);
        std::swap(codes[0], codes[1]);
    }

    // split file in codes
    if (pos[0] != std::string::npos) {
        if (pos[1] != std::string::npos) {
            std::copy_n(code.begin() + pos[0], pos[1] - pos[0], std::back_inserter(*codes[0]));
        } else {
            std::copy(code.begin() + pos[0], code.end(), std::back_inserter(*codes[0]));
        }
    }
    if (pos[1] != std::string::npos) {
        if (pos[2] != std::string::npos) {
            std::copy_n(code.begin() + pos[1], pos[2] - pos[1], std::back_inserter(*codes[1]));
        } else {
            std::copy(code.begin() + pos[1], code.end(), std::back_inserter(*codes[1]));
        }
    }
    if (pos[2] != std::string::npos) {
        std::copy(code.begin() + pos[2], code.end(), std::back_inserter(*codes[2]));
    }

    for (auto& c : codes) {
        c->erase(0, c->find_first_of('\n'));
    }
}

SourceCodeGroup CreateSourceCodeFromGroup(const std::string& code) {
    std::string vertex, geometry, fragment;
    parseShaderFile(code, vertex, geometry, fragment);
    SourceCodeGroup group;
    if (!vertex.empty())
        group.vertexCode = CreateSourceCode(vertex);
    if (!geometry.empty())
        group.geometryCode = CreateSourceCode(geometry);
    if (!fragment.empty())
        group.fragmentCode = CreateSourceCode(fragment);
    return group;
}

SourceCodeGroup CreateSourceCodeFromGroupFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.fail()) {
        Log("SourceCodeRes %s load failed", filename.c_str());
        return {nullptr, nullptr, nullptr};
    }
    std::string code((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());
    return CreateSourceCodeFromGroup(code);
}
