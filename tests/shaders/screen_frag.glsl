#version 330 core
out vec4 FragColor;
  
in vec2 axolote_tex_coord;

uniform sampler2D axolote_diffuse0;

void main()
{ 
    FragColor = texture(axolote_diffuse0, axolote_tex_coord);
}
