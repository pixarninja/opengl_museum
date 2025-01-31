/******************************************************************************
	Name: Wes and Zach Harris
	File Name: Object.h
	Synopsis: This file contains variable and function declarations for the 
			  Object class.
******************************************************************************/

#pragma once
#ifndef MODEL_VIEW_OBJECT_H
#define MODEL_VIEW_OBJECT_H

#endif //MODEL_VIEW_OBJECT_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <glm/vec3.hpp>	// glm::vec3
#include <glm/vec4.hpp>	// glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp>
// glm::translate, glm::rotate, glm::scale, glm::perspective

class Object
{
public:
	Object();
	Object(std::string fileName);
	void load(GLuint &program);
	void draw();
	void getObjInfo();
	int initVertArray(float **vertexArray);
	~Object();

    std::vector<glm::vec4> vertList;

private:
	int numVert;
	int numNorm;
	int numFaces;
	int numIndex;

	std::vector<glm::vec4> tempVertList;
	std::vector<glm::vec4> normList;
	std::vector<GLuint> vertexIndex;
	std::vector<GLuint> normalsIndex;
	glm::vec4 *vert, *color, *normal;
	GLuint *index;
	GLuint buffer, IndexBuffer;

	std::string title;
};

