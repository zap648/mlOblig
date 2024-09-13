#version 410 core

in vec2 TexCoord;
out vec4 fragmentColor;     //color sent to fragment on screen

uniform sampler2D textureSampler;

void main() {
   fragmentColor = texture(textureSampler, TexCoord);
}
