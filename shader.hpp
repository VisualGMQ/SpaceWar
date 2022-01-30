#pragma once
#include "pch.hpp"
#include "glhelpfunc.hpp"
#include "log.hpp"
#include "tool.hpp"

class SourceCode {
public:
    SourceCode(const std::string& code);
    inline bool Empty() const { return code_.empty(); }
    inline std::string& GetCode() { return code_; }
    inline const std::string& GetCode() const { return code_;}
    inline bool HasCode() const { return !code_.empty(); }

private:
    std::string code_;
};

inline std::ostream& operator<<(std::ostream& o, const SourceCode& res) {
    o << res.GetCode();
    return o;
}

class Shader final {
public:
    Shader(const SourceCode* vertex,
           const SourceCode* fragment,
           const SourceCode* geometry = nullptr);
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
    // void SetMat4(const std::string& name, const glm::mat4& mat, bool transpose = false);
    // void SetFloatVec3(const std::string& name, const glm::vec3&);

    inline void Use() const { GL_CALL(glUseProgram(program_)); }

private:
    class ShaderStruct final {
    public:
        enum Type {
            Vertex,
            Fragment,
            Geometry,
        };
        ShaderStruct(const SourceCode& code, Type type);
        ~ShaderStruct();
        ShaderStruct(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;

        inline bool Valid() const { return shader_ != 0; }

        GLuint Get() const { return shader_; }

    private:
        GLuint shader_;
    };

    GLuint program_;
    Unique<ShaderStruct> shaders_[3];
};

using SourceCodePtr = Ref<SourceCode>;
using ShaderPtr = Ref<Shader>;

struct SourceCodeGroup {
    SourceCodePtr vertexCode = nullptr;
    SourceCodePtr geometryCode = nullptr;
    SourceCodePtr fragmentCode = nullptr;
};

inline SourceCodePtr CreateSourceCode(const std::string& code) {
    if (code.empty()) {
        Log("source code is empty");
        return nullptr;
    }
    return SourceCodePtr(new SourceCode(code));
}

SourceCodePtr CreateSourceCodeFromFile(const std::string& filename);
SourceCodeGroup CreateSourceCodeFromGroup(const std::string& code);
SourceCodeGroup CreateSourceCodeFromGroupFile(const std::string& filename);

inline ShaderPtr CreateShader(const SourceCode* vertex,
                              const SourceCode* fragment,
                              const SourceCode* geometry = nullptr) {
    return ShaderPtr(new Shader(vertex, fragment, geometry));
}
