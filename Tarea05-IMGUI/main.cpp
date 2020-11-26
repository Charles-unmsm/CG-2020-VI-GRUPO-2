/* imgui */
#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw.h"
#include "imgui\imgui_impl_opengl3.h"

/* graphics header */
#include <GL\glew.h>
#include <GLFW\glfw3.h>

/* math */
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>

/* basic headers */
#include <iostream>

/* own headers */
#include "utils.h"

GLFWwindow *window;
GLuint vao, vbo;
GLuint program;

int dimVertices;
int numero_vertices;
static float colorF[4] = { 0.4f,0.3f,0.0f,1.0f };
static float colorO[4] = { 0.0f,0.4f,0.3f,1.0f };

void init(GLFWwindow *window){

		GLfloat x=0;
		GLfloat y=0;
		GLfloat z=0;
		GLfloat radio=0.05;
		GLint numero_lados=80;
		numero_vertices=numero_lados+1+1;
		GLfloat twicePi=2.0f*M_PI;

		GLfloat verticesX[numero_vertices];
		GLfloat verticesY[numero_vertices];
		GLfloat verticesZ[numero_vertices];

		verticesX[0]=x;
		verticesY[0]=x;
		verticesZ[0]=x;

		for (int i =1; i<numero_vertices;i++){
			verticesX[i]= x + (radio+cos(i*twicePi/numero_lados));
			verticesY[i]= y + (radio+sin(i*twicePi/numero_lados));
			verticesZ[i]= z ;
		}

		verticesX[numero_vertices]=verticesX[1];
		verticesY[numero_vertices]=verticesX[1];
		verticesZ[numero_vertices]=verticesX[1];



		dimVertices=numero_vertices*3;
		GLfloat m_vertices[dimVertices];

		for (int i =0; i<numero_vertices;i++){
			m_vertices[i*3]=verticesX[i];
			m_vertices[i*3+1]=verticesY[i];
			m_vertices[i*3+2]=verticesZ[i];

			}



	    /*--[INICIALIZACION IMGUI]-----------*/
	    ImGui::CreateContext();
	    ImGuiIO& io = ImGui::GetIO(); (void)io;
	    // ImGui::StyleColorsDark();
	    ImGui::StyleColorsClassic();
	    ImGui_ImplGlfw_InitForOpenGL(window, true);
	    ImGui_ImplOpenGL3_Init("#version 130");
	    /*--[INICIALIZACION IMGUI]-----------*/

	    program = createShaderProgram("vshader.glsl", "fshader.glsl" );

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		//glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), vertices, GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, dimVertices*sizeof(GLfloat), m_vertices, GL_STATIC_DRAW);

		glBindVertexArray(vao);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glDisableVertexAttribArray(0);
}

void display(){
    
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(colorF[0],colorF[1],colorF[2],colorF[3]);

    /*--[FRAME IMGUI]-----------*/
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    /*--[FRAME IMGUI]-----------*/


    static float tras_x = 0, tras_y=0;
    static float rota_x = 0, rota_y = 0;
    static float scale = 0.5;



    /*--[CODIGO IMGUI]-----------*/
    ImGui::Begin("Transformaciones"); // Aqui inicia una pequeña ventana
    ImGui::Text("Traslaciones");
    if (ImGui::Button(" Mov. Arriba ")&&tras_y<1.0f){
         tras_y=tras_y+0.1f;
    }
    ImGui::SameLine();
    if (ImGui::Button("   Mov. Abajo  ")&& tras_y>-1.0f){
    	 tras_y=tras_y-0.1f;
    }
    if (ImGui::Button(" Mov. Izquierda ")&&tras_x>-1.0f){
         tras_x=tras_x-0.1f;
    }
    ImGui::SameLine();
    if (ImGui::Button("  Mov. Derecha  ")&&tras_x<1.0f){
         tras_x=tras_x+0.1f;
    }

    ImGui::Text("Rotaciones");
	ImGui::SliderFloat("rota. x", &rota_x, -3.14 * 2.0, 3.14 * 2.0);
	ImGui::SliderFloat("rota. y", &rota_y, -3.14 * 2.0, 3.14 * 2.0);
	ImGui::Text("Escalamiento");
	ImGui::SliderFloat("Escala", &scale, 0, 1);
	ImGui::Text("Colores");
	ImGui::ColorEdit3("Color Fondo", colorF);
	ImGui::ColorEdit3("Color Objeto", colorO);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate); // Muestra los FPS de la aplicación
    ImGui::End(); // Aqui termina la ventana ultima en iniciar
    /*--[CODIGO IMGUI]-----------*/


    glUseProgram(program);
    glBindVertexArray(vao);
    glm::mat4 trans = translate(glm::mat4(1), glm::vec3(tras_x, tras_y, 0));
    trans = glm::rotate(trans, rota_x, glm::vec3(1, 0, 0));
    trans = glm::rotate(trans, rota_y, glm::vec3(0, 1, 0));
    trans = glm::scale(trans, glm::vec3(scale, scale, 1));
    glUniformMatrix4fv(glGetUniformLocation(program, "transformation_matrix"), 1, false, value_ptr(trans));
    glUniform4fv(glGetUniformLocation(program, "ColorO"),1,colorO);

    glDrawArrays(GL_TRIANGLE_FAN, 0, numero_vertices);



    /*--[RENDER IMGUI]-----------*/
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    /*--[RENDER IMGUI]-----------*/


}

int main(){
    if (!glfwInit()) return 1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* window = glfwCreateWindow(800, 800, "Tarea05-IMGUI", NULL, NULL);
    if (window == NULL) return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    if (glewInit() != GLEW_OK) return 1;

    init(window);

    while (!glfwWindowShouldClose(window)){
        glfwPollEvents();
        display();
        glfwSwapBuffers(window);
    }

    /*--[CLEAN IMGUI]-----------*/
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    /*--[CLEAN IMGUI]-----------*/

}
