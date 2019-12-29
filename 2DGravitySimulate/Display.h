#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Color.h"

typedef unsigned int unsint;

struct glObjects {
	unsint VAO;
	unsint VBO;
};

struct vec3d {
	float x;
	float y;
	float z;
};

class Display {
	GLFWwindow* window;
	Color defaultDrawColor = Color(DefaultColor::RED, 1.0f);
	Color clearColor = Color(0.2f, 0.3f, 0.3f, 1.0f);
	unsint shaderProgram = 0;
	const char* drawColorUniform = "ourColor";
	bool isShaderProgramUsed = false;
	glObjects objectsPlaceholder;
public:
	Display(GLFWwindow* _window) : Display(_window, Color(DefaultColor::RED, 1.0f), Color(0.2f, 0.3f, 0.3f, 1.0f)) {};
	Display(GLFWwindow*, Color, Color);
	Display(GLFWwindow*, unsint);
	Display(GLFWwindow*, unsint, Color, Color);
	GLFWwindow* getWindow();
	bool windowShouldClose();
	void setWindowShouldClose(bool);
	Color getClearColor();
	void setClearColor(Color);
	void clear();
	void swapBuffers();
	void pollEvents();
	int getShaderProgram();
	void useShaderProgram(int);
	const char* getDrawColorUniform();
	void setDrawColorUniform(const char*);
	glObjects createObjects(float*,unsint);
	void bind(glObjects);
	void releaseSpase(glObjects);
	void drawArrays(GLenum, GLint, GLsizei);
	void drawLine(vec3d, vec3d);
	void drawLine(vec3d, vec3d, Color);
	void drawTrangleSoild(vec3d, vec3d, vec3d);
	void drawTrangleSoild(vec3d, vec3d, vec3d, Color);
	void drawTrangleHollow(vec3d, vec3d, vec3d);
	void drawTrangleHollow(vec3d, vec3d, vec3d, Color);
	void drawCircle(vec3d, float);
	void drawCircle(vec3d, float, Color);
};