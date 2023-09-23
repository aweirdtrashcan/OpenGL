#version 330 core

out vec4 outColor;

in vec2 texCoord;

uniform sampler2D tex;

void main() {
    outColor = texture(tex, texCoord);
}