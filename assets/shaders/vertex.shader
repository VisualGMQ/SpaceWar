#version 330 core
layout (location = 0) in vec4 aVertex;

uniform mat4 ortho;
uniform mat4 view;
uniform mat4 model;

out vec2 TexCoord;

void main() {
    gl_Position = ortho * view * model * vec4(aVertex.xy, 0, 1);
    TexCoord = aVertex.zw;
}


