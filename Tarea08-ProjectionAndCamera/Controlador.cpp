

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Include GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw.h"
#include "imgui\imgui_impl_opengl3.h"


#include <string>
#include <fstream>
#include <cmath>
#include <stack>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Controlador.h"


#define numVAOs 1
#define numVBOs 3

glm::vec3 cameraPos;
glm::vec3 cameraFront;
glm::vec3 cameraUp;
GLuint renderingProgram,renderingProgram1,renderingProgram2;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

bool BulletInstanced=false;

glm::mat4 pMat, vMat, mMat, mvMat;
int width, height;
float aspecto;
GLint numberOfVertices;
double TiempoDisparo;

int Score=0;

Controlador::Controlador(){}

void Controlador::LoadStaticObjects(){

	float cubeLargePositions[108] = {
	-1.0f, 1.0f, -1.5f, -1.0f, -1.0f, -1.5f, 1.0f,-1.0f, -1.5f, //1
	1.0f, -1.0f, -1.5f, 1.0f, 1.0f, -1.5f, -1.0f, 1.0f,-1.5f, //2
	1.0f, -1.0f, -1.5f, 1.0f, -1.0f, 1.5f, 1.0f, 1.0f, -1.5f, //3
	1.0f, -1.0f, 1.5f, 1.0f, 1.0f, 1.5f, 1.0f, 1.0f, -1.5f,  //4
	1.0f, -1.0f,1.5f, -1.0f, -1.0f, 1.5f, 1.0f, 1.0f, 1.5f,  //5
	-1.0f, -1.0f, 1.5f,-1.0f, 1.0f, 1.5f, 1.0f, 1.0f, 1.5f, //6
	-1.0f, -1.0f, 1.5f, -1.0f,-1.0f, -1.5f, -1.0f, 1.0f, 1.5f, //7
	-1.0f, -1.0f, -1.5f, -1.0f, 1.0f,-1.5f, -1.0f, 1.0f, 1.5f, //8
	-1.0f, -1.0f, 1.5f, 1.0f, -1.0f, 1.5f,1.0f, -1.0f, -1.5f, //9
	1.0f, -1.0f, -1.5f, -1.0f, -1.0f, -1.5f, -1.0f,-1.0f,1.5f, //10
	-1.0f, 1.0f, -1.5f, 1.0f, 1.0f, -1.5f, 1.0f, 1.0f,1.5f, //11
	1.0f, 1.0f, 1.5f, -1.0f, 1.0f, 1.5f, -1.0f, 1.0f, -1.5f, }; //12

	GLfloat radius = 0.5f;
	GLint numberOfSides = 100;
	numberOfVertices = numberOfSides+2;
	GLfloat twicePi = 2.0f * M_PI;

	GLfloat verticesX[numberOfVertices];
	GLfloat verticesY[numberOfVertices];
	GLfloat verticesZ[numberOfVertices];

			verticesX[0] = 0;
			verticesY[0] = 0;
			verticesZ[0] = 0;
			for (int i = 0; i < numberOfVertices; i++) {
				verticesX[i] = 0 + (radius * cos(i * twicePi / numberOfSides));
				verticesY[i] = 0 ;
				verticesZ[i] = 0 + (radius * sin(i * twicePi / numberOfSides));
			}
			GLint dimVertices = (numberOfVertices) * 3;
			GLfloat m_Vertices[dimVertices];

			for (int i = 0; i < numberOfVertices; i++) {
				m_Vertices[i * 3] = verticesX[i];
				m_Vertices[i * 3 + 1] = verticesY[i];
				m_Vertices[i * 3 + 2] = verticesZ[i];
			}

			float cubePositions[108] = {
									-0.25f, 0.25f, 1.0f, -0.25f, -0.25f, 1.0f, 0.25f,-0.25f, 1.0f, //1
									0.25f, -0.25f, 1.0f, 0.25f, 0.25f, 1.0f, -0.25f, 0.25f,1.0f, //2
									0.25f, -0.25f, 1.0f, 0.25f, -0.25f, 1.5f, 0.25f, 0.25f, 1.0f, //3
									0.25f, -0.25f, 1.5f, 0.25f, 0.25f, 1.5f, 0.25f, 0.25f, 1.0f,  //4
									0.25f, -0.25f,1.5f, -0.25f, -0.25f, 1.5f, 0.25f, 0.25f, 1.5f,  //5
									-0.25f, -0.25f, 1.5f,-0.25f, 0.25f, 1.5f, 0.25f, 0.25f, 1.5f, //6
									-0.25f, -0.25f, 1.5f, -0.25f,-0.25f, 1.0f, -0.25f, 0.25f, 1.5f, //7
									-0.25f, -0.25f, 1.0f, -0.25f, 0.25f,1.0f, -0.25f, 0.25f, 1.5f, //8
									-0.25f, -0.25f, 1.5f, 0.25f, -0.25f, 1.5f,0.25f, -0.25f, 1.0f, //9
									0.25f, -0.25f, 1.0f, -0.25f, -0.25f, 1.0f, -0.25f,-0.25f,1.5f, //10
									-0.25f, 0.25f, 1.0f, 0.25f, 0.25f, 1.0f, 0.25f, 0.25,1.5f, //11
									0.25f, 0.25f, 1.5f, -0.25f, 0.25f, 1.5f, -0.25f, 0.25f, 1.0f, };









		glGenVertexArrays(numVAOs, vao);
		glBindVertexArray(vao[0]);
		glGenBuffers(numVBOs, vbo);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeLargePositions), cubeLargePositions,
				GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), m_Vertices,
						GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubePositions), cubePositions,
		GL_STATIC_DRAW);

}


void Controlador::SetupCamera(GLFWwindow *window){

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsClassic();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
	renderingProgram1 = Utils::createShaderProgram("vshader.glsl", "fshader.glsl");
	renderingProgram2 = Utils::createShaderProgram("Ovshader.glsl", "Ofshader.glsl");
	renderingProgram = Utils::createShaderProgram("bvshader.glsl", "bfshader.glsl");
	glfwGetFramebufferSize(window, &width, &height);
	aspecto = (float) width / (float) height;
	pMat = glm::perspective(glm::radians(45.0f), aspecto, 0.1f, 1000.0f);

	cameraPos   = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
	cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);
	Controlador::LoadStaticObjects();

}

void Controlador::Draw(GLFWwindow *window,double currentTime){
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

    static float rota_Nx = 3.14*0.25, rota_Ny = 0;
    static float rota_Cx = -3.14*0.25, rota_Cy = 0;
    static float Trans_Cx = 0,Trans_Cy = 20, Trans_Cz =-20;
    static float Velocidad=1.0f;

	ImGui::Begin("Transformaciones");
	ImGui::Text("Rotaciones de Cañon");
	ImGui::SliderFloat("rota. x", &rota_Nx, 0, 3.14 * 0.5);
	ImGui::SliderFloat("rota. y", &rota_Ny, -3.14 * 0.5, 3.14 * 0.5);
	ImGui::Text("Rotaciones de Cámara");
	ImGui::SliderFloat("rota. Cámara x", &rota_Cx, -3.14 * 0.5,3.14 * 0.5);
	ImGui::SliderFloat("rota. Cámara y", &rota_Cy, -3.14 * 0.5, 3.14 * 0.5);
	ImGui::Text("Translaciones de camara");
	ImGui::SliderFloat("Trans. Cámara x", &Trans_Cx, -10, 10);
	ImGui::SliderFloat("Trans. Cámara y", &Trans_Cy, 0, 30);
	ImGui::SliderFloat("Trans. Cámara z", &Trans_Cz, -40, 40);
	ImGui::SliderFloat("Velocidad", &Velocidad, 1.0f, 4.0f);
	if (ImGui::Button(" Disparar ")){
		BulletInstanced=true;
		TiempoDisparo=currentTime;
	}
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate); // Muestra los FPS de la aplicación
	ImGui::Text("Score: %3i ",Score);
	ImGui::End();


	mMat=glm::rotate(glm::mat4(1.0f), -rota_Cx,
					glm::vec3(1., 0, 0));
	mMat*=glm::rotate(glm::mat4(1.0f), -rota_Cy,
					glm::vec3(0, 1, 0));

	mMat*= glm::translate(glm::mat4(1.0f), glm::vec3(-Trans_Cx, -Trans_Cy, Trans_Cz));

	glm::mat4 view = glm::lookAt(cameraPos, cameraFront, cameraUp);
	view=mMat*view;


	vMat= glm::rotate(glm::mat4(1.0f), -rota_Nx,
				glm::vec3(1, 0, 0));
	vMat=glm::rotate(vMat, -rota_Ny,
			glm::vec3(0, 1, 0));

	glUseProgram(renderingProgram2);
	GLuint viewLoc = glGetUniformLocation(renderingProgram2, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	GLuint projLoc = glGetUniformLocation(renderingProgram2, "proj_matrix");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, numberOfVertices,6);

				if(BulletInstanced){
					double time=currentTime-TiempoDisparo;
					float a=0;
					float b=(5*Velocidad*glm::sin(rota_Cx)*time)-(0.098*time*time)/2.0;
					float c=10*Velocidad*glm::cos(rota_Cx)*time;
					glm::mat4 mVel=glm::translate(glm::mat4(1.0f), glm::vec3(a, b, c));
						if(time>15/Velocidad){
						BulletInstanced=false;
						Score+=10;
				}else{
							glUseProgram(renderingProgram);
							GLuint viewLoc = glGetUniformLocation(renderingProgram, "view");
							glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
							GLuint projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
							GLuint velLoc = glGetUniformLocation(renderingProgram, "Velocity");
							glUniformMatrix4fv(velLoc, 1, GL_FALSE, glm::value_ptr(mVel));
							GLuint mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
							glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
							glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(vMat));
							glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
							glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
							glEnableVertexAttribArray(0);
							glDrawArrays(GL_TRIANGLES, 0, 36);
					}
				}







		glUseProgram(renderingProgram1);
		 viewLoc = glGetUniformLocation(renderingProgram1, "view");
		 projLoc = glGetUniformLocation(renderingProgram1, "proj_matrix");
		GLuint mvLoc = glGetUniformLocation(renderingProgram1, "mv_matrix");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(vMat));
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLES, 0, 36);

	    ImGui::Render();
	    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}



