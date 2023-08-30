#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 tex_coord;
in vec3 normal;
in vec3 current_pos;

uniform float ambient;
uniform vec3 camera_pos;

uniform vec4 light_color;
uniform vec3 light_pos;
uniform bool is_light_color_set;

uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform bool is_tex_set;

void main()
{
    vec4 temp_frag_color = vec4(color, 1.0f);
    if (is_tex_set)
    {
        temp_frag_color = texture(diffuse0, tex_coord);
    }
    if (is_light_color_set)
    {
        vec3 normal = normalize(normal);
        vec3 light_direction = normalize(light_pos - current_pos);
        float diffuse = max(dot(normal, light_direction), 0.0f);

        float specular_light = 0.75f;
        vec3 view_direction = normalize(camera_pos - current_pos);
        vec3 reflection_direction = reflect(-light_direction, normal);
        float spec_amount = pow(max(dot(view_direction, reflection_direction), 0.0f), 16);
        float specular = spec_amount * specular_light;

        temp_frag_color = (texture(diffuse0, tex_coord) * (diffuse + ambient)
                           + texture(specular0, tex_coord).r * specular) * light_color;
    }

    FragColor = temp_frag_color;
}
