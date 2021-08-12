// FRAGMENT SHADER
// Fragment shader is all about color of a given pixel
// lights, shadows, color of the light, etc are all impl. here

#version 430 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}