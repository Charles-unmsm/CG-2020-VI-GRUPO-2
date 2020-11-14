//============================================================================
// Name        : Diseño de una figura
// Professor   : Herminio Paucar
// Version     :
// Description : Utilizamos los Vertex y Fragment Shaders
//============================================================================

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

// Vertex array object (VAO)
GLuint m_VAO[4];

// Vertex buffer object (VBO)
GLuint *m_VBO;

// color buffer object (CBO)
GLuint *m_CBO;

// GLSL program from the shaders
GLuint programID;

GLuint VAO_Pointer=0;
GLuint VBO_Pointer=0;
GLuint CBO_Pointer=0;

GLint WindowWidth = 600;
GLint WindowHeight = 600;

GLint numberOfVertices;

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
void draw (int Mode_Type){
    // Use our shader
    glUseProgram(programID);

    // create transformations
    //glm::mat4 model = glm::mat4(1.0f);
    //glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 mvp = glm::ortho(-40.0f, 40.0f, -40.0f, 40.0f);

    // Our ModelViewProjection : multiplication of our 3 matrices
    //glm::mat4 mvp = projection * view * model;
    // Remember, matrix multiplication is the other way around

    // retrieve the matrix uniform locations
    GLuint matrix = glGetUniformLocation(programID, "mvp");
    glUniformMatrix4fv(matrix, 1, GL_FALSE, &mvp[0][0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[VBO_Pointer]);
    glVertexAttribPointer(
                          0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
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




    glDrawArrays(mode[Mode_Type], 0, numberOfVertices);



    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
void transferDataToGPUMemory(int i){

    	programID = Utils::createShaderProgram("src/vertShader.glsl", "src/fragShader.glsl");
    	glGenVertexArrays(4, m_VAO);
    	switch(i){
    	case 1:
    	m_VBO= new GLuint[4];
    	m_CBO= new GLuint[4];
    	glBindVertexArray(m_VAO[0]);
    	glGenBuffers(4, m_VBO);
    	glGenBuffers(4, m_CBO);
    	GenerarCirculo(20.0, 0.0f,0.0f,0.0f,1.0f,1.0f,0.0f);
    	draw(5);
    	GenerarCirculo(20.0, 0.0f,0.0f,0.0f,0.0f,0.0f,0.0f);
    	draw(3);
    	VBO_Pointer++;
    	CBO_Pointer++;
    	GenerarCirculo(3.0, 5.0f,5.0f,0.0f,1.0f,1.0f,1.0f);
    	draw(5);
    	GenerarCirculo(3.0, 5.0f,5.0f,0.0f,0.0f,0.0f,0.0f);
    	draw(3);
    	VBO_Pointer++;
    	CBO_Pointer++;
    	GenerarCirculo(3.0, -5.0f,5.0f,0.0f,1.0f,1.0f,1.0f);
    	draw(5);
    	GenerarCirculo(3.0, -5.0f,5.0f,0.0f,0.0f,0.0f,0.0f);
    	draw(3);
    	VBO_Pointer++;
    	CBO_Pointer++;
    	GenerarSemiCirculo(10.0, 0.0f,-2.0f,0.0f,180,0.0f,0.0f,0.0f);
    	draw(2);
    	VBO_Pointer=0;
    	CBO_Pointer=0;
    	break;

    	case 2:
    	m_VBO= new GLuint[5];
    	m_CBO= new GLuint[5];
    	glBindVertexArray(m_VAO[1]);
    	glGenBuffers(5, m_VBO);
    	glGenBuffers(5, m_CBO);
    	GenerarSemiCirculo(10.0, 20.0f,0.0f,0.0f,215,0.0f,0.0f,0.0f);
    	draw(2);
    	VBO_Pointer++;
    	CBO_Pointer++;
    	GenerarCirculo(20.0, 0.0f,0.0f,0.0f,1.0f,0.0f,1.0f);
    	draw(5);
       	GenerarCirculo(20.0, 0.0f,0.0f,0.0f,0.0f,0.0f,0.0f);
    	draw(3);
     	VBO_Pointer++;
    	CBO_Pointer++;
    	GenerarCirculo(8.0, 10.0f,30.0f,0.0f,1.0f,0.0f,1.0f);
    	draw(5);
    	GenerarCirculo(8.0, 10.0f,30.0f,0.0f,0.0f,0.0f,0.0f);
    	draw(3);
    	VBO_Pointer++;
    	CBO_Pointer++;
    	GenerarCirculo(8.0, -10.0f,30.0f,0.0f,1.0f,0.0f,1.0f);
    	draw(5);
    	GenerarCirculo(8.0, -10.0f,30.0f,0.0f,0.0f,0.0f,0.0f);
    	draw(3);
    	VBO_Pointer++;
    	CBO_Pointer++;
    	GenerarCirculo(10.0, 0.0f,20.0f,0.0f,1.0f,0.0f,1.0f);
    	draw(5);
    	GenerarCirculo(10.0, 0.0f,20.0f,0.0f,0.0f,0.0f,0.0f);
    	draw(3);
    	VBO_Pointer=0;
    	CBO_Pointer=0;
    	break;

    	case 3:
    	m_VBO= new GLuint[13];
    	m_CBO= new GLuint[13];
    	glBindVertexArray(m_VAO[2]);
    	glGenBuffers(13, m_VBO);
    	glGenBuffers(13, m_CBO);
    	GenerarRectangulo(20.0,30.0, 15.0f,10.0f,0.0f,0.0824f,0.698f,0.858f);
    	draw(4);
    	//GenerarPerimetroRectangulo(20.0,30.0, 15.0f,10.0f,0.0f,0.0f,0.0f,0.0f);
    	//draw(3);
    	VBO_Pointer++;
    	CBO_Pointer++;
    	GenerarRectangulo(10.0,5.0, 2.5f,-5.0f,0.0f,0.0724f,0.598f,0.758f);
    	draw(4);
    	//GenerarPerimetroRectangulo(10.0,5.0, 2.5f,-5.0f,0.0f,0.0f,0.0f,0.0f);
    	//draw(3);
    	VBO_Pointer++;
    	CBO_Pointer++;
    	GenerarRectangulo(10.0,5.0, 7.5f,-5.0f,0.0f,0.0824f,0.698f,0.858f);
    	draw(4);
    	//GenerarPerimetroRectangulo(10.0,5.0, 7.5f,-5.0f,0.0f,0.0f,0.0f,0.0f);
    	//draw(3);
    	VBO_Pointer++;
    	CBO_Pointer++;
    	GenerarRectangulo(10.0,5.0, 22.5f,-5.0f,0.0f,0.0724f,0.598f,0.758f);
    	draw(4);
    	//GenerarPerimetroRectangulo(10.0,5.0, 22.5f,-5.0f,0.0f,0.0f,0.0f,0.0f);
    	//draw(3);
    	VBO_Pointer++;
    	CBO_Pointer++;
    	GenerarRectangulo(10.0,5.0, 27.5f,-5.0f,0.0f,0.0824f,0.698f,0.858f);
    	draw(4);
    	//GenerarPerimetroRectangulo(10.0,5.0, 27.5f,-5.0f,0.0f,0.0f,0.0f,0.0f);
    	//draw(3);
    	VBO_Pointer++;
    	CBO_Pointer++;
    	GenerarCirculo(4.0, -11.5f,3.0f,0.0f,0.0724f,0.598f,0.758f);
    	draw(5);
    	//GenerarCirculo(4.0, -11.5f,3.0f,0.0f,0.0f,0.0f,0.0f);
    	//draw(3);
    	VBO_Pointer++;
    	CBO_Pointer++;
    	GenerarCirculo(1.0, -11.0f,-7.0f,0.0f,0.0824f,0.698f,0.858f);
    	draw(5);
    	//GenerarCirculo(1.0, -11.0f,-7.0f,0.0f,0.0f,0.0f,0.0f);
    	//draw(3);
    	VBO_Pointer++;
    	CBO_Pointer++;
    	GenerarCirculo(2.0, -10.0f,-5.0f,0.0f,0.0724f,0.598f,0.758f);
    	draw(5);
    	//GenerarCirculo(2.0, -10.0f,-5.0f,0.0f,0.0f,0.0f,0.0f);
    	//draw(3);
    	VBO_Pointer++;
    	CBO_Pointer++;
    	GenerarCirculo(3.0, -9.0f,-2.0f,0.0f,0.0824f,0.698f,0.858f);
    	draw(5);
    	//GenerarCirculo(3.0, -9.0f,-2.0f,0.0f,0.0f,0.0f,0.0f);
    	//draw(3);
    	VBO_Pointer++;
    	CBO_Pointer++;
    	GenerarCirculo(8.0, -8.0f,10.0f,0.0f,0.0824f,0.698f,0.858f);
    	draw(5);
    	//GenerarCirculo(8.0, -8.0f,10.0f,0.0f,0.0f,0.0f,0.0f);
    	//draw(3);
    	VBO_Pointer++;
    	CBO_Pointer++;
    	GenerarCirculo(1.5, -9.0f,8.0f,0.0f,1.0f,1.0f,1.0f);
    	draw(5);
    	//GenerarCirculo(1.5, -9.0f,8.0f,0.0f,0.0f,0.0f,0.0f);
    	//draw(3);
    	VBO_Pointer++;
    	CBO_Pointer++;
    	GenerarRectangulo(10.0,5.0, -3.0f,10.0f,0.0f,0.0824f,0.698f,0.858f);
    	draw(4);
    	//GenerarPerimetroRectangulo(5.0,4.0, -4.0f,10.0f,0.0f,0.0f,0.0f,0.0f);
    	//draw(3);
    	VBO_Pointer++;
    	CBO_Pointer++;
    	GenerarRectangulo(8.0,4.0, -4.0f,10.0f,0.0f,0.737f,0.458f,0.741f);
    	draw(4);
    	VBO_Pointer=0;
    	CBO_Pointer=0;
    	break;

    	case 4:
    	m_VBO= new GLuint[9];
    	m_CBO= new GLuint[9];
    	glBindVertexArray(m_VAO[3]);
    	glGenBuffers(9, m_VBO);
    	glGenBuffers(9, m_CBO);
    	//cabeza
    	GenerarRectangulo(13.0,13.0, 3.5f,31.0f,0.0f,0.956f,0.988f,0.231f);
    	draw(4);
    	//GenerarPerimetroRectangulo(13.0,13.0, 3.5f,31.0f,0.0f,0.0f,0.0f,0.0f);
    	//draw(3);
    	VBO_Pointer++;
    	CBO_Pointer++;
    	//brazo izquierdo
    	GenerarRectangulo(30.0,10.0, -14.5f,10.0f,0.0f,0.956f,0.988f,0.231f);
    	draw(4);
    	//GenerarPerimetroRectangulo(30.0,10.0, -14.5f,10.0f,0.0f,0.0f,0.0f,0.0f);
    	//draw(3);
    	VBO_Pointer++;
    	CBO_Pointer++;
    	//brazo derecha
    	GenerarRectangulo(30.0,10.0, 20.5f,10.0f,0.0f,0.956f,0.988f,0.231f);
    	draw(4);
    	//GenerarPerimetroRectangulo(30.0,10.0, 20.5f,10.0f,0.0f,0.0f,0.0f,0.0f);
    	//draw(3);
    	VBO_Pointer++;
    	CBO_Pointer++;
    	//pierna izquierda
    	GenerarRectangulo(25.0,10.0, -4.0f,-23.0f,0.0f,0.552f,0.721f,0.337f);
    	draw(4);
    	//GenerarPerimetroRectangulo(25.0,10.0, -4.0f,-23.0f,0.0f,0.0f,0.0f,0.0f);
    	//draw(3);
    	VBO_Pointer++;
    	CBO_Pointer++;
    	//pierna derecha
    	GenerarRectangulo(25.0,10.0, 10.0f,-23.0f,0.0f,0.552f,0.721f,0.337f);
    	draw(4);
    	//GenerarPerimetroRectangulo(25.0,10.0, 10.0f,-23.0f,0.0f,0.0f,0.0f,0.0f);
    	//draw(3);
    	VBO_Pointer++;
    	CBO_Pointer++;
    	//torso
    	GenerarRectangulo(40.0,25.0, 3.0f,5.0f,0.0f,0.305f,0.580f,0.854f);
    	draw(4);
    	//GenerarPerimetroRectangulo(40.0,25.0, 3.0f,5.0f,0.0f,0.0f,0.0f,0.0f);
    	//draw(3);
    	VBO_Pointer++;
    	CBO_Pointer++;
    	//ojo izquierdo
    	GenerarRectangulo(2.0,2.0, 1.0f,33.0f,0.0f,0.0f,0.0f,0.0f);
    	draw(4);
    	//GenerarPerimetroRectangulo(2.0,2.0, 1.0f,33.0f,0.0f,0.0f,0.0f,0.0f);
    	//draw(3);
    	VBO_Pointer++;
    	CBO_Pointer++;
    	//ojo derecho
    	GenerarRectangulo(2.0,2.0, 6.0f,33.0f,0.0f,0.0f,0.0f,0.0f);
    	draw(4);
    	//GenerarPerimetroRectangulo(2.0,2.0, 6.0f,33.0f,0.0f,0.0f,0.0f,0.0f);
    	//draw(3);
    	VBO_Pointer++;
    	CBO_Pointer++;
    	//boca
    	GenerarRectangulo(2.0,8.0, 3.5f,28.0f,0.0f,0.0f,0.0f,0.0f);
    	draw(4);
    	//GenerarPerimetroRectangulo(2.0,8.0, 3.5f,28.0f,0.0f,0.0f,0.0f,0.0f);
    	//draw(3);
    	VBO_Pointer++;
    	CBO_Pointer++;

    	VBO_Pointer=0;
    	CBO_Pointer=0;
    	break;
    	}


}

//--------------------------------------------------------------------------------
void cleanupDataFromGPU(){
    glDeleteBuffers(1, m_VBO);
    glDeleteBuffers(1, m_CBO);
    glDeleteVertexArrays(1, m_VAO);
    glDeleteProgram(programID);
}



int main( void )
{
    // Initialise GLFW
    glfwInit();

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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


    GLuint FramebufferName = 0;
    glGenFramebuffers(1, &FramebufferName);
    //glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
    // render scene for each frame
    do{
        // White background
        glClearColor(0.905f, 0.772f, 0.419f, 0.0f);

        // Clear the screen
        glClear( GL_COLOR_BUFFER_BIT );

        //left bottom
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, WindowWidth*0.5, WindowHeight*0.5);
        transferDataToGPUMemory(3);


        //right bottom
        glViewport(WindowWidth*0.5, 0, WindowWidth*0.5, WindowHeight*0.5);
        transferDataToGPUMemory(4);
        //aca poner robot

        //left top
        glViewport(0, WindowHeight*0.5, WindowWidth*0.5, WindowHeight*0.5);
        transferDataToGPUMemory(2);


        //right top
        glViewport(WindowWidth*0.5, WindowHeight*0.5, WindowWidth*0.5, WindowHeight*0.5);
        transferDataToGPUMemory(1);


        // Swap buffers
        glfwSwapBuffers(window);
        // looking for events
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );

    // delete framebuffer
    glDeleteFramebuffers(1, &FramebufferName);

    // Cleanup VAO, VBOs, and shaders from GPU
    cleanupDataFromGPU();

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

