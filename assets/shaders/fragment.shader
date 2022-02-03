#version 330 core

uniform sampler2D Texture;
uniform vec4 aColor;
in vec2 TexCoord;

out vec4 FragColor;

void main() {
    FragColor = texture(Texture, TexCoord) * aColor;
}
