#version 430 core

layout(location=0) out vec4 color;

uniform vec4 ColorO;

void main() {
    color = ColorO;

}