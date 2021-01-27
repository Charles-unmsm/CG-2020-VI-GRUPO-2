#version 430 core

layout (location=0) in vec3 position;  // coord

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform mat4 view;
uniform mat4 Velocity;
out vec4 varyingColor;  // be interpolated by the rasterizer
mat4 buildTranslate(float x, float y, float z);

void main(void) {


    gl_Position =proj_matrix*view*Velocity*mv_matrix*vec4(position, 1.0);  
    varyingColor = vec4(position, 1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 0.5);
}

mat4 buildTranslate(float x, float y, float z) {
    mat4 trans = mat4(1.0, 0.0, 0.0, 0.0,
                      0.0, 1.0, 0.0, 0.0,
                      0.0, 0.0, 1.0, 0.0,
                      x,   y,   z,   1.0f);
    return trans;
 }