// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>


#include "Utils.h"

// GLM header file
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLFWwindow* window;

using namespace glm;

GLuint m_VAO;

GLuint *m_VBO;

GLuint *m_CBO;

GLuint programID;

GLuint VAO_Pointer=0;
GLuint VBO_Pointer=0;
GLuint CBO_Pointer=0;

GLint WindowWidth = 600;
GLint WindowHeight = 600;

GLint numberOfVertices;

float x = 0.0f;
float inc = 0.01f;


void GenerarCirculo(GLfloat Radio, GLfloat x, GLfloat y, GLfloat z,GLfloat R, GLfloat G , GLfloat B){

		GLfloat radius = Radio;
		GLint numberOfSides = 100;
		numberOfVertices = numberOfSides+2;
		GLfloat twicePi = 2.0f * M_PI;

		GLfloat verticesX[numberOfVertices];
		GLfloat verticesY[numberOfVertices];
		GLfloat verticesZ[numberOfVertices];

		verticesX[0] = x;
		verticesY[0] = y;
		verticesZ[0] = z;
		for (int i = 0; i < numberOfVertices; i++) {
			verticesX[i] = x + (radius * cos(i * twicePi / numberOfSides));
			verticesY[i] = y + (radius * sin(i * twicePi / numberOfSides));
			verticesZ[i] = z;
		}
		GLint dimVertices = (numberOfVertices) * 3;
		GLfloat m_Vertices[dimVertices];
		GLfloat m_Colores[dimVertices];


		for (int i = 0; i < numberOfVertices; i++) {
			m_Vertices[i * 3] = verticesX[i];
			m_Vertices[i * 3 + 1] = verticesY[i];
			m_Vertices[i * 3 + 2] = verticesZ[i];
			m_Colores[i * 3] = R;
			m_Colores[i * 3 + 1] = G;
			m_Colores[i * 3 + 2] = B;
		}


		glBindBuffer(GL_ARRAY_BUFFER, m_VBO[VBO_Pointer]);
		glBufferData(
		    GL_ARRAY_BUFFER,
		    sizeof(m_Vertices),
			m_Vertices,
		    GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_CBO[CBO_Pointer]);
			glBufferData(
			GL_ARRAY_BUFFER,
			sizeof(m_Colores),
			m_Colores,
			GL_STATIC_DRAW);

}

void GenerarSemiCirculo(GLfloat Radio, GLfloat x, GLfloat y, GLfloat z,GLuint A,GLfloat R, GLfloat G , GLfloat B){

		GLfloat radius = Radio;
		GLint numberOfSides = 100;
		numberOfVertices = numberOfSides/2;
		GLfloat twicePi = 2.0f * M_PI;
		GLfloat verticesX[numberOfVertices];
		GLfloat verticesY[numberOfVertices];
		GLfloat verticesZ[numberOfVertices];
		//x=x+(radius * cos(A * twicePi / 360));
		//y=y+(radius * sin(A * twicePi / 360));
		verticesX[0] = (radius * cos(twicePi *A / 360));
		verticesY[0] = (radius * sin(twicePi* A / 360));
		verticesZ[0] = z;
		int aux=numberOfSides*A/360;

		for (int i=aux-1; i <aux+numberOfVertices; i++) {
			verticesX[i-(aux)] = x + (radius * cos(i * twicePi / numberOfSides));
			verticesY[i-(aux)] = y + (radius * sin(i * twicePi / numberOfSides));
			verticesZ[i-(aux)] = z;
		}



		GLint dimVertices = ((numberOfVertices)) * 3;
		GLfloat m_Vertices[dimVertices];
		GLfloat m_Colores[dimVertices];

		for (int i = 0; i < numberOfVertices; i++) {
			m_Vertices[i * 3] = verticesX[i];
			m_Vertices[i * 3 + 1] = verticesY[i];
			m_Vertices[i * 3 + 2] = verticesZ[i];
			m_Colores[i * 3] = R;
			m_Colores[i * 3 + 1] = G;
			m_Colores[i * 3 + 2] = B;
		}

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO[VBO_Pointer]);
		glBufferData(
		    GL_ARRAY_BUFFER,
		    sizeof(m_Vertices),
			m_Vertices,
		    GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_CBO[CBO_Pointer]);
			glBufferData(
			GL_ARRAY_BUFFER,
			sizeof(m_Colores),
			m_Colores,
			GL_STATIC_DRAW);

}
void GenerarRectangulo(GLfloat Altura, GLfloat Base, GLfloat x, GLfloat y, GLfloat z,GLfloat R, GLfloat G , GLfloat B){
	GLfloat m_Vertices[18]={
		x-Base/2, y-Altura/2, z,
		x-Base/2, y+Altura/2, z,
		x+Base/2, y-Altura/2, z,
		x+Base/2, y-Altura/2, z,
		x+Base/2, y+Altura/2, z,
		x-Base/2, y+Altura/2, z,
	};
	numberOfVertices=6;
	GLfloat m_Colores[18]={
		R,G,B,
		R,G,B,
		R,G,B,
		R,G,B,
		R,G,B,
		R,G,B,
	};


	glBindBuffer(GL_ARRAY_BUFFER, m_VBO[VBO_Pointer]);
	glBufferData(
	GL_ARRAY_BUFFER,
	sizeof(m_Vertices),
	m_Vertices,
	GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_CBO[CBO_Pointer]);
	glBufferData(
	GL_ARRAY_BUFFER,
	sizeof(m_Colores),
	m_Colores,
	GL_STATIC_DRAW);



}

void GenerarTriangulo(GLfloat Altura, GLfloat Base, GLfloat x, GLfloat y, GLfloat z,GLfloat R, GLfloat G , GLfloat B){
	GLfloat m_Vertices[9]={
		x-Base/2, y-Altura/2, z,
		x, y+Altura/2, z,
		x+Base/2, y-Altura/2, z,
	};
	numberOfVertices=3;
	GLfloat m_Colores[9]={
		R,G,B,
		R,G,B,
		R,G,B,
	};


	glBindBuffer(GL_ARRAY_BUFFER, m_VBO[VBO_Pointer]);
	glBufferData(
	GL_ARRAY_BUFFER,
	sizeof(m_Vertices),
	m_Vertices,
	GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_CBO[CBO_Pointer]);
	glBufferData(
	GL_ARRAY_BUFFER,
	sizeof(m_Colores),
	m_Colores,
	GL_STATIC_DRAW);



}


void GenerarLinea(GLfloat x1, GLfloat y1,GLfloat x2, GLfloat y2){
	GLfloat m_Vertices[6]={
			x1, y1, 0.0f,
			x2, y2, 0.0f,
		};
	numberOfVertices=2;
	GLfloat m_Colores[6]={
			0.0f,0.0f,0.0f,
			0.0f,0.0f,0.0f,
		};
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO[VBO_Pointer]);
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(m_Vertices),
		m_Vertices,
		GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_CBO[CBO_Pointer]);
		glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(m_Colores),
		m_Colores,
		GL_STATIC_DRAW);
}

void GenerarPerimetroRectangulo(GLfloat Altura, GLfloat Base, GLfloat x, GLfloat y, GLfloat z,GLfloat R, GLfloat G , GLfloat B){
	GLfloat m_Vertices[12]={
		x-Base/2, y+Altura/2, z,
		x-Base/2, y-Altura/2, z,
		x+Base/2, y-Altura/2, z,
		x+Base/2, y+Altura/2, z,
	};
	numberOfVertices=4;
	GLfloat m_Colores[12]={
		R,G,B,
		R,G,B,
		R,G,B,
		R,G,B,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO[VBO_Pointer]);
	glBufferData(
	GL_ARRAY_BUFFER,
	sizeof(m_Vertices),
	m_Vertices,
	GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_CBO[CBO_Pointer]);
	glBufferData(
	GL_ARRAY_BUFFER,
	sizeof(m_Colores),
	m_Colores,
	GL_STATIC_DRAW);



}

//--------------------------------------------------------------------------------
void draw (int Mode_Type, int Option){
    glUseProgram(programID);

    glm::mat4 mvp = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f);
    GLuint matrix = glGetUniformLocation(programID, "mvp");
    glUniformMatrix4fv(matrix, 1, GL_FALSE, &mvp[0][0]);
    GLuint Opt=glGetUniformLocation(programID, "Opt");
    glProgramUniform1i(programID,Opt,Option);
    GLuint rotateLoc = glGetUniformLocation(programID, "rotate");
    glProgramUniform1f(programID, rotateLoc, glfwGetTime());
    x += inc;
    if (x > 1.0f) inc = -0.01f;
    if (x < -1.0f) inc = 0.01f;
    GLuint offsetLoc = glGetUniformLocation(programID, "offset");
    glProgramUniform1f(programID, offsetLoc, x);


    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[VBO_Pointer]);
    glVertexAttribPointer(
                          0,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, m_CBO[CBO_Pointer]);
    glVertexAttribPointer(
                          1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                          3,                                // size
                          GL_FLOAT,                         // type
                          GL_FALSE,                         // normalized?
                          0,                                // stride
                          (void*)0                          // array buffer offset
                          );
    GLenum mode[7] = {
    				GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP,
    				GL_TRIANGLES, GL_TRIANGLE_FAN, GL_TRIANGLE_STRIP };



    if(Option==1){
    glDrawArrays(mode[Mode_Type], 0, numberOfVertices);
    }else if(Option==2){
    glDrawArraysInstanced(mode[Mode_Type], 0, numberOfVertices, 12);
    }else if(Option==3){
    glDrawArraysInstanced(mode[Mode_Type], 0, numberOfVertices, 2);
    }else{
    glDrawArrays(mode[Mode_Type], 0, numberOfVertices);
    }




    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
void transferDataToGPUMemory(int i){

    	programID = Utils::createShaderProgram("src/vertShader.glsl", "src/fragShader.glsl");
    	glGenVertexArrays(1, &m_VAO);
    	m_VBO= new GLuint[13];
    	m_CBO= new GLuint[13];
    	glBindVertexArray(m_VAO);
    	glGenBuffers(13, m_VBO);
    	glGenBuffers(13, m_CBO);
    	GenerarTriangulo(40.0,60.0, 0.0f,80.0f,0.0f,0.3725f,0.2118f,0.078f);
    	draw(4,1);
    	VBO_Pointer++;
    	CBO_Pointer++;
    	GenerarRectangulo(60.0,40.0, 0.0f,30.0f,0.0f,0.3725f,0.2118f,0.078f);
    	draw(4,1);
    	VBO_Pointer++;
    	CBO_Pointer++;
    	GenerarRectangulo(10.0,50.0, 0.0f,-5.0f,0.0f,0.3725f,0.2118f,0.078f);
    	draw(4,1);
    	VBO_Pointer++;
       	CBO_Pointer++;
    	GenerarRectangulo(80.0,40.0, 0.0f,-45.0f,0.0f,0.3725f,0.2118f,0.078f);
    	draw(4,1);
    	VBO_Pointer++;
       	CBO_Pointer++;
       	GenerarRectangulo(10.0,50.0, 0.0f,-90.0f,0.0f,0.3725f,0.2118f,0.078f);
       	draw(4,1);
       	VBO_Pointer++;
       	CBO_Pointer++;
       	GenerarRectangulo(70.0,30.0, 0.0f,-45.0f,0.0f,0.0275f,0.6078f,0.5922f);
       	draw(4,1);
       	VBO_Pointer++;
       	CBO_Pointer++;
       	GenerarCirculo(15.0,0.0f,30.0f,0.0f,1.0f,1.0f,1.0f);
       	draw(5,1);
       	VBO_Pointer++;
       	CBO_Pointer++;
       	GenerarCirculo(10.0,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f);
       	draw(5,2);
       	VBO_Pointer++;
       	CBO_Pointer++;
       	GenerarLinea(0.0f,30.0f,0.0f,40.0f);
       	draw(2,3);
       	VBO_Pointer++;
       	CBO_Pointer++;
       	GenerarLinea(0.0f,-10.0f,0.0f,-60.0f);
       	draw(2,4);
       	VBO_Pointer++;
       	CBO_Pointer++;
       	GenerarCirculo(8.0,0.0f,-60.0f,0.0f,0.8902f,0.7682f,0.0824f);
       	draw(5,4);
       	VBO_Pointer=0;
       	CBO_Pointer=0;


}

//--------------------------------------------------------------------------------
void cleanupDataFromGPU(){
    glDeleteBuffers(1, m_VBO);
    glDeleteBuffers(1, m_CBO);
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteProgram(programID);
}



int main( void )
{
    // Initialise GLFW
    glfwInit();

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window
    window = glfwCreateWindow( 600, 600, "Tarea 03-Primitivas", NULL, NULL);

    // Create window context
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    glewInit();

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // transfer my data (vertices, colors, and shaders) to GPU side
    glfwSwapInterval(1);

    //glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
    // render scene for each frame
    do{
    	glClear(GL_DEPTH_BUFFER_BIT);
    	glClearColor(1.0, 1.0, 1.0, 1.0);
    	glClear(GL_COLOR_BUFFER_BIT);

        transferDataToGPUMemory(3);

        glfwSwapBuffers(window);
        // looking for events
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );

    // delete framebuffer

    // Cleanup VAO, VBOs, and shaders from GPU
    cleanupDataFromGPU();

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

