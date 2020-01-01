#include "Display.h"
#include <cmath>

namespace TEMP {
	float tempVertices[] = { 0,0,0 };
	vec3d buf = { 0,0,0 };
	vec3d buf1 = { 0,0,0 };
}

Display::Display(GLFWwindow* _window, Color _defaultDrawColor, Color _clearColor) {
	window = _window;
	defaultDrawColor = _defaultDrawColor;
	clearColor = _clearColor;

	objectsPlaceholder = createObjects(TEMP::tempVertices, 1);
	bind(objectsPlaceholder);
}

Display::Display(GLFWwindow* _window, unsint shaderProgram): Display(_window) {
	useShaderProgram(shaderProgram);
}

Display::Display(GLFWwindow* _window, unsint shaderProgram, Color _defaultDrawColor, Color _clearColor): Display(_window, _defaultDrawColor, _clearColor) {
	useShaderProgram(shaderProgram);
}

GLFWwindow* Display::getWindow() {
	return window;
}

bool Display::windowShouldClose() {
	return glfwWindowShouldClose(window);
}

void Display::setWindowShouldClose(bool should) {
	glfwSetWindowShouldClose(window, should);
}

Color Display::getClearColor() {
	return clearColor;
}

void Display::setClearColor(Color color) {
	clearColor = color;
}

void Display::clear() {
	glClearColor(clearColor.getRed(), clearColor.getGreen(), clearColor.getBlue(), clearColor.getAlpha());
	glClear(GL_COLOR_BUFFER_BIT);
}

void Display::swapBuffers() {
	glfwSwapBuffers(window);
}

void Display::pollEvents() {
	glfwPollEvents();
}

int Display::getShaderProgram() {
	return shaderProgram;
}

void Display::useShaderProgram(int _shaderProgram) {
	shaderProgram = _shaderProgram;
	glUseProgram(shaderProgram);
	isShaderProgramUsed = true;
}

const char* Display::getDrawColorUniform() {
	return drawColorUniform;
}

void Display::setDrawColorUniform(const char* _drawColorUniform) {
	drawColorUniform = _drawColorUniform;
}

glObjects Display::createObjects(float* vertices, unsint length) {

	unsint VBO, VAO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * length, vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	return { VAO,VBO };

}

void Display::bind(glObjects objects) {
	glBindVertexArray(objects.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, objects.VBO);
}

void Display::releaseSpase(glObjects objects) {
	glDeleteBuffers(1,&objects.VBO);
	glDeleteVertexArrays(1, &objects.VAO);
	bind(objectsPlaceholder);
}

void Display::drawArrays(GLenum mode, GLint first, GLsizei count) {
	glDrawArrays(mode, first, count);
}

void Display::drawLine(vec3d vertex1, vec3d vertex2) {
	drawLine(vertex1, vertex2, defaultDrawColor);
}

void Display::drawLine(vec3d vertex1, vec3d vertex2, Color color) {

	if (isShaderProgramUsed) {
		int vertexColorLoction = glGetUniformLocation(shaderProgram, drawColorUniform);
		glUniform4f(vertexColorLoction, color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
	}

	float vertices[] = { vertex1.x,vertex1.y,vertex1.z,vertex2.x,vertex2.y,vertex2.z };
	glObjects objects = createObjects(vertices, 6);
	bind(objects);
	drawArrays(GL_LINES, 0, 2);
	releaseSpase(objects);

}

void Display::drawTrangleSoild(vec3d vertex1, vec3d vertex2, vec3d vertex3) {
	drawTrangleSoild(vertex1, vertex2, vertex3, defaultDrawColor);
}

void Display::drawTrangleSoild(vec3d vertex1, vec3d vertex2, vec3d vertex3, Color color) {

	if (isShaderProgramUsed) {
		int vertexColorLoction = glGetUniformLocation(shaderProgram, drawColorUniform);
		glUniform4f(vertexColorLoction, color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
	}

	float vertices[] = { vertex1.x,vertex1.y,vertex1.z,vertex2.x,vertex2.y,vertex2.z,vertex3.x,vertex3.y,vertex3.z };
	glObjects objects = createObjects(vertices, 9);
	bind(objects);
	drawArrays(GL_TRIANGLES, 0, 3);
	releaseSpase(objects);

}

void Display::drawTrangleHollow(vec3d vertex1, vec3d vertex2, vec3d vertex3) {
	drawTrangleHollow(vertex1, vertex2, vertex3, defaultDrawColor);
}

void Display::drawTrangleHollow(vec3d vertex1, vec3d vertex2, vec3d vertex3, Color color) {
	drawLine(vertex1, vertex2, color);
	drawLine(vertex1, vertex3, color);
	drawLine(vertex2, vertex3, color);
}

void Display::drawCircle(vec3d center, float r) {
	drawCircle(center, r, defaultDrawColor);
}

void Display::drawCircle(vec3d center, float r, Color color) {
	float offset = 0.002;
	for (float x = center.x - r; x < center.x + r; x += offset) {
		float naiveY = sqrt(r * r - pow(x - center.x, 2));
		float y = naiveY + center.y;
		float y1 = -naiveY + center.y;
		TEMP::buf.x = x;
		TEMP::buf.y = y;
		TEMP::buf.z = center.z;
		TEMP::buf1.x = x;
		TEMP::buf1.y = y1;
		TEMP::buf.z = center.z;
		drawLine(TEMP::buf, TEMP::buf1, color);
	}
}
