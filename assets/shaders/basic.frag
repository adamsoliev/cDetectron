// FRAGMENT SHADER
// Fragment shader is all about color of a given pixel
// lights, shadows, color of the light, etc are all impl. here

#version 430 core
out vec4 FragColor;

in vec3 ourColor;

void main() {
    FragColor = vec4(ourColor, 1.0f);
}