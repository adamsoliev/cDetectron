#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 frag_pos;
out vec2 frag_texture;
out vec3 frag_normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    // aPos in world space
    frag_pos = vec3(model * vec4(aPos, 1.0f));

    //flips the texture horizontal
    frag_texture = aTexCoords;

    // Get normal vectors in world space only and exclude normal translation
    frag_normal = mat3(transpose(inverse(model))) * aNormal;
}