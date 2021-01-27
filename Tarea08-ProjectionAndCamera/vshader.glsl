#version 430 core

layout (location=0) in vec3 position;  // coord

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform mat4 view;

out vec4 varyingColor;  // be interpolated by the rasterizer


void main(void) {

    gl_Position = proj_matrix *view*mv_matrix * vec4(position, 1.0);  
    varyingColor = vec4(1.0) ;
}

