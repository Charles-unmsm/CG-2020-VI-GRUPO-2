#include <stdio.h>
#include <stdlib.h>
#include <iostream>


#include "imgui\imgui_impl_glfw.h"
#include "imgui\imgui_impl_opengl3.h"
#include "imgui\imgui.h"


// Include GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <cmath>
#include <stack>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Controlador.h"
using namespace std;

glm::mat4 pMatr;
float aspect;

void window_size_callback(GLFWwindow* win, int newWidth, int newHeight) {
    aspect = (float)newWidth / (float)newHeight;
    glViewport(0, 0, newWidth, newHeight);
    pMatr = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
}



int main(void) {
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);     //
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); 	// Resizable option.

	GLFWwindow *window = glfwCreateWindow(800, 800, "Tarea 8-Projection and Camera", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		exit(EXIT_FAILURE);
	}
	glfwSwapInterval(1);
	Controlador CTRL;
	//glfwSetWindowSizeCallback(window, window_size_callback);

	CTRL.SetupCamera(window);
	while (!glfwWindowShouldClose(window)) {
		CTRL.Draw(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	 ImGui_ImplOpenGL3_Shutdown();
	 ImGui_ImplGlfw_Shutdown();
	 ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);

}

