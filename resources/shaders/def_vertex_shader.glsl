#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;
layout (location = 3) in vec3 aNormal;

out vec3 color;
out vec2 tex_coord;
out vec3 normal;
out vec3 current_pos;

uniform bool is_simple_mesh;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;

mat4 camera()
{
    return projection * view;
}

void main()
{
    current_pos = vec3(model * vec4(aPos, 1.0f));
    tex_coord = aTex;

    gl_Position = camera() * vec4(current_pos, 1.0f);
    color = aColor;

    // These operations seems to fix the "rotation problem"
    // but it's considered costly
    normal = mat3(transpose(inverse(model))) * aNormal;
}
