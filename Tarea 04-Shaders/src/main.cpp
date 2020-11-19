/*
 * main.cpp
 *
 *  Created on: 17 nov. 2020
 *      Author: Hiroshi
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Include GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include "Utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

GLFWwindow* window;

using namespace glm;

GLint WindowWidth = 600;
GLint WindowHeight = 600;
GLuint programID;
GLfloat* m_Vertices;
GLuint n_Vertices;
GLuint m_VBO;
GLuint m_VAO;
void init (GLFWwindow* window) {

	// Utils
	programID = Utils::createShaderProgram("src/vertShader.glsl", "src/fragShader.glsl");

	// The first 3 points are to Vertex position of Triangle
    n_Vertices = 18;
    m_Vertices = new GLfloat[18] {
			-1.0f, -1.0f, 0.0f, //Triangle 01
			-1.0f, 1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			-1.0f, 1.0f, 0.0f, //Triangle 02
			1.0f, -1.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
	};

	// Cria um ID na GPU para um array de  buffers
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	// Cria um ID na GPU para nosso buffer
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	// Reserva memoria na GPU para um TARGET receber dados
	// Copia esses dados pra essa área de memoria
	glBufferData(
			GL_ARRAY_BUFFER,	// TARGET associado ao nosso buffer
			18 * sizeof(GLfloat),	// tamanho do buffer
			m_Vertices,			// Dados a serem copiados pra GPU
			GL_STATIC_DRAW		// Política de acesso aos dados, para otimização
		);

	// Nesse ponto, ja copiamos nossos dados pra GPU.
	glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(GLvoid*) 0
		);

	glEnableVertexAttribArray(0);	// Habilita este atributo

	glBindVertexArray(0);
}


void draw(double currentTime,GLFWwindow* window){
	glUseProgram(programID);
	GLuint uniformResolution = glGetUniformLocation(programID, "u_resolution");
	//glm::vec2 u_resolution = glm::vec2(WindowWidth,WindowHeight);
	glUniform2f(uniformResolution, 800.0f,800.0f);
	GLuint uniformTime = glGetUniformLocation(programID, "u_time");
	glUniform1f(uniformTime, currentTime);
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}


int main (void){

	// Initialise GLFW
	 if (!glfwInit()) {
	    	exit(EXIT_FAILURE);
	    }
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  //
	    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            //
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); 	// Resizable option.

	    GLFWwindow* window = glfwCreateWindow(800, 800, "Lab06.0: Translate of Triangle", NULL, NULL);
	    glfwMakeContextCurrent(window);
	    if (glewInit() != GLEW_OK) {
	    	exit(EXIT_FAILURE);
	    }
	    glfwSwapInterval(1);

	    //init(window);
	    //double CurrentTime=glfwGetTime();

	    while (!glfwWindowShouldClose(window)) {
	     init(window);
	     draw(glfwGetTime(),window);
		 glfwSwapBuffers(window);
		 glfwPollEvents();

		}


	glDeleteProgram(programID);

	glfwTerminate();
	return 0;
}
