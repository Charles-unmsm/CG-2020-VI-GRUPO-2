

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
#include <cmath>
#include <stack>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Utils.h"
class Controlador{
public:
	Controlador();
	void LoadStaticObjects();
	void CreateBullet();
	void UpdateScore();
	void SetupCamera(GLFWwindow *window);
	void Draw(GLFWwindow *window,double currentTime);


};
