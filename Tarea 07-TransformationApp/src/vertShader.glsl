#version 410 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColor;

uniform mat4 mvp;
uniform int Opt;
uniform float rotate;
uniform float offset;


out vec3 fragmentColor;
const float radius = 0.125;
const float pi = 3.141592653589793;
const float twicePi = 2*pi;
const float numberOfSides = 12;

mat4 buildTranslate(float x, float y, float z) {
    mat4 trans = mat4(1.0, 0.0, 0.0, 0.0,
                      0.0, 1.0, 0.0, 0.0,
                      0.0, 0.0, 1.0, 0.0,
                      x,   y,   z,   1.0);
    return trans;
}

mat4 buildScale(float sx, float sy, float sz) {
    mat4 scale = mat4( sx, 0.0, 0.0, 0.0,
                      0.0,  sy, 0.0, 0.0,
                      0.0, 0.0,  sz, 0.0,
                      0.0, 0.0, 0.0, 1.0);
    return scale;
}
mat4 buildRotateZ(float rad) {
    mat4 zrot = mat4(cos(rad), -sin(rad), 0.0, 0.0,
                     sin(rad), cos(rad),  0.0, 0.0,
                     0.0,      0.0,       1.0, 0.0,
                     0.0,      0.0,       0.0, 1.0);
    return zrot;
}
void main()
{	
	float i = gl_InstanceID;
	float x_vertex;
	float y_vertex;
	if(Opt==2){
	x_vertex = radius * cos(i * twicePi / numberOfSides);
	y_vertex = 0.3+radius * sin(i * twicePi / numberOfSides);
	mat4 localTrans = buildTranslate(x_vertex, y_vertex, 0);
	mat4 localScal = buildScale(0.1, 0.1, 0);
	gl_Position=localTrans * localScal * mvp*vec4(vertexPosition, 1.0);
    }else if(Opt==1){
	gl_Position = mvp*vec4(vertexPosition, 1.0);
	}else if(Opt==3){
	mat4 localRotaZ ;
	mat4 localTrans1 = buildTranslate(0,-0.30, 0);
	mat4 localTrans2 = buildTranslate(0,0.30, 0);
	mat4 localScal ;
	if(gl_InstanceID==0){
	localScal = buildScale(1, 1, 0);
	localRotaZ = buildRotateZ(60*rotate * twicePi / 360);
	}
	else{
	localScal = buildScale(0.5, 0.5, 0);
	localRotaZ = buildRotateZ(4*rotate * twicePi / 360);
	}
	gl_Position=localTrans2*localScal*localRotaZ*localTrans1*mvp*vec4(vertexPosition, 1.0);

	}else{
	mat4 localTrans1 = buildTranslate(0, 0.10, 0);
	mat4 localTrans2 = buildTranslate(0, -0.10, 0);
	mat4 localRotaZ = buildRotateZ(9.5*offset * twicePi / 360);
	mat4 localScal = buildScale(1, 1, 0);
	gl_Position =localTrans2* localRotaZ*localTrans1 * localScal*mvp*vec4(vertexPosition, 1.0);
	}
	
	
	fragmentColor = vertexColor;

}

