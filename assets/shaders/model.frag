#version 430 core

out vec4 FragColor;

in vec3 frag_pos;
in vec2 frag_texture;
in vec3 frag_normal;

// UNIFORMS
uniform vec3 light_color;
uniform vec3 light_pos;
uniform vec3 view_pos;

uniform sampler2D texture_diffuse1;

void main() {
    /*Phong lighting model calculations to generate ambient, diffuse, and specular components*/

    //Calculate Ambient Lighting
    float ambient_strength = 0.05f; //Set ambient or global lighting strength
    //Generate ambient light color
    vec3 ambient = ambient_strength * light_color;

    //Calculate Diffuse Lighting
    vec3 norm = normalize(frag_normal); //Normalize vectors to 1 unit
    vec3 light_direction = normalize(light_pos - frag_pos); //Calculate distance (light direction) between light source and fragments/pixels on
    float impact = max(dot(norm, light_direction), 0.0); //Calculate diffuse impact by generating dot product of normal and light
    vec3 diffuse = impact * light_color; //Generate diffuse light color

    //Calculate Specular lighting
    float specular_intensity = 0.1f; //Set specular light strength
    float highlight_size = 128.0f; //Set specular highlight size
    vec3 view_dir = normalize(view_pos - frag_pos); //Calculate view direction
    //Calculate reflection vector
    vec3 reflect_dir = reflect(-light_direction, norm);
    //Calculate specular component
    float specular_component = pow(max(dot(view_dir, reflect_dir), 0.0), highlight_size);
    vec3 specular = specular_intensity * specular_component * light_color;

    //Calculate phong result
    vec3 object_color = texture(texture_diffuse1, frag_texture).xyz;
    vec3 phong = (ambient + diffuse + specular) * object_color;
    FragColor = vec4(phong, 1.0f); //Send lighting results to GPU
}