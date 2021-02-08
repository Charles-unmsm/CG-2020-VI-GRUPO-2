/*
 * main.cpp
 *
 *  Created on: 6 feb. 2021
 *      Author: Hiroshi
 */

#include <iostream>
#include <fstream>
#include <sstream>

#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/aruco/charuco.hpp>
#include <opencv2/calib3d.hpp>
#include "../include/marker_detect.h"
#include "../include/cube.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/shader.h"

#include <strings.h>
#include <vector>
#include <math.h>

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int width_window = 640, height_window = 480;


const float PI = 3.14159265358979323846;
float FinalPhi=2*PI;
float FinalTeta=PI;
int i=0;
int j=1;
float radio=10;
float teta;
float phi;
float increRad=(float)(PI/20);
float Vertice1x,Vertice1y, Vertice1z=0;
float Vertice2x,Vertice2y, Vertice2z=0;
float Vertice3x,Vertice3y, Vertice3z=0;
float Vertice4x,Vertice4y, Vertice4z=0;
int numVertices;



int main(int argc, char **argv)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(width_window, height_window, "Proyecto CV", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    if(window == nullptr){
    	std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
    }
	glewExperimental = GL_TRUE;

	if(glewInit() != GLEW_OK){
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);


	glfwGetFramebufferSize(window, &width_window, &height_window);
	glViewport(0, 0, width_window, height_window);
	std::cerr << "Ventana creada." << std::endl;



	cv::Mat frame;
	cv::Mat rot_mat;
	cv::Mat intrinsic_matrix;
	cv::Mat distortion_parameters;

	cv::VideoCapture cap;
	int id_camera=1;
	cap.open(id_camera);
	 if (!cap.isOpened()) {
	        std::cerr << "failed to open camera (id=1)." << std::endl;
	        return 1;
	    }


	marker marker1(argv, intrinsic_matrix, distortion_parameters);


	Shader suzanne_shader("src/shaders/suzanne_vertex_shader.vert", "src/shaders/suzanne_fragment_shader.frag");
	Shader bg_shader("src/shaders/bg_vertex_shader.vert", "src/shaders/bg_fragment_shader.frag");
	Shader lamp_shader("src/shaders/lamp_vertex_shader.vert", "src/shaders/lamp_fragment_shader.frag");
	std::cerr << "Shaders creado." << std::endl;


	std::vector<GLuint> indices;
	int SizeTotal=(FinalPhi/increRad)*(FinalTeta/increRad);
	    float esferaPositions[SizeTotal*18];
	    numVertices=SizeTotal*6;
		for(teta=0;teta<FinalTeta;teta+=increRad){
			for(phi=0;phi<FinalPhi;phi+=increRad){
										Vertice1z=(radio)*((float) sin(teta))*((float)cos(phi));
					                    Vertice1x=(radio)*((float) sin(teta))*((float)sin(phi));
					                    Vertice1y=(radio)*((float) cos(teta));
					                    Vertice1z=(radio)*((float) sin(teta))*((float)cos(phi));
					                                  //VERTICE 2
					                    Vertice2z=(radio)*((float) sin(teta+increRad))*((float)cos(phi));
					                    Vertice2x=(radio)*((float) sin(teta+increRad))*((float)sin(phi));
					                    Vertice2y=(radio)*((float) cos(teta+increRad));
					                                  //VERTICE 3
					                    Vertice3z=(radio)*((float) sin(teta+increRad))*((float)cos(phi+increRad));
					                    Vertice3x=(radio)*((float) sin(teta+increRad))*((float)sin(phi+increRad));
					                    Vertice3y=(radio)*((float) cos(teta+increRad));
					                                  //VERTICE 4
					                   Vertice4z=(radio)*((float) sin(teta))*((float)cos(phi+increRad));
					                    Vertice4x=(radio)*((float) sin(teta))*((float)sin(phi+increRad));
					                    Vertice4y=(radio)*((float) cos(teta));


					                     esferaPositions[i*18]=Vertice1x;
										 esferaPositions[i*18+1]=Vertice1y;
										 esferaPositions[i*18+2]=Vertice1z;

										 esferaPositions[i*18+3]=Vertice2x;
										 esferaPositions[i*18+4]=Vertice2y;
										 esferaPositions[i*18+5]=Vertice2z;

										 esferaPositions[i*18+6]=Vertice3x;
										 esferaPositions[i*18+7]=Vertice3y;
										 esferaPositions[i*18+8]=Vertice3z;

										 esferaPositions[i*18+9]=Vertice1x;
										 esferaPositions[i*18+10]=Vertice1y;
										 esferaPositions[i*18+11]=Vertice1z;

										 esferaPositions[i*18+12]=Vertice3x;
										 esferaPositions[i*18+13]=Vertice3y;
										 esferaPositions[i*18+14]=Vertice3z;

										 esferaPositions[i*18+15]=Vertice4x;
										 esferaPositions[i*18+16]=Vertice4y;
										 esferaPositions[i*18+17]=Vertice4z;

										indices.push_back((float)1.5*sin(teta)*sin(phi));
										indices.push_back((float)1.5*cos(teta));
										indices.push_back((float)1.5*sin(teta)*cos(phi));
							i++;
		}
		}
		std::cerr << "Imagen cargada." << std::endl;


	GLuint *indices_array = indices.data();
	GLuint size_of_indices_array = indices.size()*sizeof(GLuint);



	GLuint VBO_suzanne, VAO_suzanne, EBO_suzanne;
	glGenBuffers(1, &EBO_suzanne);
	glGenVertexArrays(1, &VAO_suzanne);
	glGenBuffers(1, &VBO_suzanne);
	glBindVertexArray(VAO_suzanne);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_suzanne);
	glBufferData(GL_ARRAY_BUFFER, sizeof(esferaPositions) ,esferaPositions, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_suzanne);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_of_indices_array, indices_array, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	std::cerr << "Vertices creados." << std::endl;


	glm::mat4 model_suzanne;
	model_suzanne= glm::scale(model_suzanne, glm::vec3(0.05f, 0.05f, 0.05f));
	model_suzanne= glm::translate(model_suzanne, glm::vec3(0.0f, 0.0f, 10.0f));
	float near = 0.2f;
	float far = 1000.0f;
	float fx = 612.9770191846128f;
	float fy = 612.9770191846128f;
	float cx = 319.5;
	float cy = 239.5;
	glm::mat4 perspective_projection = {fx/cx, 0, 0, 0, 0, fy/cy, 0, 0, 0, 0, -(far+near)/(far-near), -(2*far*near)/(far-near), 0, 0, -1, 0};
	perspective_projection = glm::transpose(perspective_projection);
	std::cerr <<fx <<" " <<fy  << std::endl;
	std::cerr <<cx <<" " <<cy  << std::endl;


	GLfloat lamp_vertices[] = {
	-0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f,
	-0.5f, -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f,  0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f,  0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f};


	GLuint VBO_lamp, VAO_lamp;
	glGenVertexArrays(1, &VAO_lamp);
	glGenBuffers(1, &VBO_lamp);
	glBindVertexArray(VAO_lamp);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_lamp);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lamp_vertices), lamp_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	std::cerr << "Lampara creada." << std::endl;



	GLfloat vertices_bg[] = {
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, 0.0f,  1.0f, 1.0f, -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, -0.5f, -0.5f, 0.0f,  0.0f, 0.0f};



	GLuint VBO_bg, VAO_bg;
	glGenVertexArrays(1, &VAO_bg);
	glGenBuffers(1, &VBO_bg);
	glBindVertexArray(VAO_bg);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_bg);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_bg), vertices_bg, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);


	cap.read(frame);

	int width = frame.size().width;
	int height = frame.size().height;
	GLuint texture_bg;
	glGenTextures(1, &texture_bg);
	glBindTexture(GL_TEXTURE_2D, texture_bg);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, frame.data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	std::cerr << "Fondo definido." << std::endl;


	glm::mat4 modelview_bg = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, -499, 0, 0, 0, 1};
	modelview_bg = glm::transpose(modelview_bg);
	modelview_bg = glm::scale(modelview_bg, glm::vec3(998*cx/fx, 998*cy/fy, 0));


	float ambient_strength = 0.3f;
	glm::vec3 light_color = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 ambient_light = ambient_strength * light_color;
	std::cerr << "Comienzo de iteración." << std::endl;
	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
        glClearColor(0.27f, 0.27f, 0.27f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if(cap.grab())
			cap.read(frame);
		glm::mat4 modelview_suzanne= {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 10, 0, 0, 0, 1};
		rot_mat=cv::Mat::zeros(3,3,CV_64F);
		//marker1.marker_detect(frame);
		if(marker1.marker_detect(frame))
		{
			cv::Rodrigues(marker1.rvecs, rot_mat);
			std::cerr << "Rodrigues realizado." << std::endl;
			modelview_suzanne = {rot_mat.at<double>(0,0), rot_mat.at<double>(0,1), rot_mat.at<double>(0,2), marker1.tvecs.at<double>(0), -rot_mat.at<double>(1,0), -rot_mat.at<double>(1,1), -rot_mat.at<double>(1,2), -marker1.tvecs.at<double>(1), -rot_mat.at<double>(2,0), -rot_mat.at<double>(2,1), -rot_mat.at<double>(2,2), -marker1.tvecs.at<double>(2), 0.0f, 0.0f, 0.0f, 1.0f};

		}

		modelview_suzanne = glm::transpose(modelview_suzanne);



		float time = glfwGetTime();
		float lamp_pos_x = 9*sin(time)+15.5f;
		float lamp_pos_y = 9*cos(time)+10.0f;
		float lamp_pos_z = -9.0f;

		glUseProgram(suzanne_shader.program);
		glBindVertexArray(VAO_suzanne);
		glUniformMatrix4fv(glGetUniformLocation(suzanne_shader.program, "model_suzanne"), 1, GL_FALSE, glm::value_ptr(model_suzanne));
		glUniformMatrix4fv(glGetUniformLocation(suzanne_shader.program, "modelview_suzanne"), 1, GL_FALSE, glm::value_ptr(modelview_suzanne));
		glUniformMatrix4fv(glGetUniformLocation(suzanne_shader.program, "perspective_projection_suzanne"), 1, GL_FALSE, glm::value_ptr(perspective_projection));
		glUniform3f(glGetUniformLocation(suzanne_shader.program, "ambient_light"), ambient_light.x, ambient_light.y, ambient_light.z);
		glUniform3f(glGetUniformLocation(suzanne_shader.program, "lamp_pos"), lamp_pos_x, lamp_pos_y, lamp_pos_z);
		glUniform3f(glGetUniformLocation(suzanne_shader.program, "light_color"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(suzanne_shader.program, "suzanne_color"), 0.0f, 0.4f, 0.4f);
		glUniform3f(glGetUniformLocation(suzanne_shader.program, "camera_pos"), 0.0f, 0.0f, 0.0f);
		glDrawArrays(GL_TRIANGLES, 0, numVertices);
		glBindVertexArray(0);
		std::cerr << "Bola Dibujada." << std::endl;

		glUseProgram(bg_shader.program);
		glBindVertexArray(VAO_bg);
		glActiveTexture(GL_TEXTURE0);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame.cols, frame.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, frame.data);
		glBindTexture(GL_TEXTURE_2D, texture_bg);
		glUniform1i(glGetUniformLocation(bg_shader.program, "webcam_texture"), 0);
		glUniformMatrix4fv(glGetUniformLocation(bg_shader.program, "modelview_bg"), 1, GL_FALSE, glm::value_ptr(modelview_bg));
		glUniformMatrix4fv(glGetUniformLocation(bg_shader.program, "perspective_projection_bg"), 1, GL_FALSE, glm::value_ptr(perspective_projection));
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		std::cerr << "Fondo dibujado." << std::endl;





		glUseProgram(lamp_shader.program);
		glBindVertexArray(VAO_lamp);
		glm::mat4 model_lamp = {2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, lamp_pos_x, lamp_pos_y, lamp_pos_z, 1.0f};
		model_lamp = glm::rotate(model_lamp, glm::radians(sin(time)*90.0f), glm::vec3(1.0f, 1.0f, 0.0f));
		model_lamp = glm::rotate(model_lamp, glm::radians(sin(time)*90.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(glGetUniformLocation(lamp_shader.program, "model_lamp"), 1, GL_FALSE, glm::value_ptr(model_lamp));
		glUniformMatrix4fv(glGetUniformLocation(lamp_shader.program, "modelview_lamp"), 1, GL_FALSE, glm::value_ptr(modelview_suzanne));
		glUniformMatrix4fv(glGetUniformLocation(lamp_shader.program, "projection_lamp"), 1, GL_FALSE, glm::value_ptr(perspective_projection));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		std::cerr << "Lampara dibujada." << std::endl;
		glfwSwapBuffers(window);
		char key = (char)cv::waitKey(100);
		 	        if (key == 27) // ascii 27 = ESC
		 	            break;


	}

	glDeleteVertexArrays(1, &VAO_suzanne);
	glDeleteBuffers(1, &VBO_suzanne);
	glDeleteVertexArrays(1, &VAO_bg);
	glDeleteBuffers(1, &VBO_bg);
	glDeleteVertexArrays(1, &VAO_lamp);
	glDeleteBuffers(1, &VBO_lamp);

	glfwTerminate();
	return EXIT_SUCCESS;
}

