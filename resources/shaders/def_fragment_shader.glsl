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
uniform bool is_specular_map_set;

float get_specular_map()
{
    if (is_specular_map_set)
        return texture(specular0, tex_coord).r;
    else
        return color.r;
}

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

        float specular_light = 0.25f;
        vec3 view_direction = normalize(camera_pos - current_pos);
        vec3 reflection_direction = reflect(-light_direction, normal);
        float spec_amount = pow(max(dot(view_direction, reflection_direction), 0.0f), 16);
        float specular = spec_amount * specular_light;

        vec3 diffuse_light_color = temp_frag_color.rgb * (diffuse + ambient);

        float specular_map = get_specular_map();
        float specular_light_color = specular_map * specular;

        vec3 temp_frag_light = (diffuse_light_color + specular_light_color) * light_color.rgb;

        temp_frag_color = vec4(temp_frag_light, light_color.a);
    }

    FragColor = temp_frag_color;
}
