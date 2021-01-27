#version 430 core

layout (location=0) in vec3 position;  // coord

uniform mat4 proj_matrix;
uniform mat4 view;

out vec4 varyingColor;  // be interpolated by the rasterizer

//mat4 buildRotateX(float rad);
//mat4 buildRotateY(float rad);
//mat4 buildRotateZ(float rad);
mat4 buildTranslate(float x, float y, float z);
mat4 buildScale(float sx, float sy, float sz);
void main(void) {
//	
    int i = gl_InstanceID ;	  
//
//    mat4 localRotX = buildRotateX(1.75 * i);
//    mat4 localRotY = buildRotateY(1.75 * i);
//    mat4 localRotZ = buildRotateZ(1.75 * i);
//
	float a;
	float c;
	
   if(i%3==0){
   a = -2.0f;
   }else if(i%3==1){
   a = 2.0f;
   }else{
   a = 0.0f;
   }

   if(i%2==0){
   c=20.0f;
   }else{
   c=16.0f;
   }
   
   
   varyingColor=vec4(1.0f);
    mat4 localTrans = buildTranslate(a, 0.0f, c);
    gl_Position = proj_matrix *view*localTrans * vec4(position, 1.0);  
   

 


}


//// builds and returns a translation matrix
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