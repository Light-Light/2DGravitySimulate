#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <time.h>
#include <windows.h>
#include "Display.h"
#include "Star.h"
#include "GravitySystem.h"

using std::cout;
using std::endl;
using std::cerr;

const char* fragmentShaderSource1 = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"	FragColor = ourColor;\n"
"}\0";

const char* vertexShaderSource1 = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main(){\n"
"gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
"}\0";

const int width = 800;
const int height = 800;
const float fps = 10000;
const float displayArea = 200;

bool pause = false;

GLFWwindow* window;

void init();
void keyPress(GLFWwindow*, int, int, int, int);
void mouseClick(GLFWwindow*, int, int, int);


int main() {

	srand(time(NULL));

	init();

	unsint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource1, NULL);
	glCompileShader(vertexShader);

	unsint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource1, NULL);
	glCompileShader(fragmentShader);

	unsint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	Display display = Display(window, shaderProgram);
	display.setClearColor(Color(DefaultColor::BLACK, 1.0f));

	GravitySystem gs = GravitySystem(displayArea);
	
	
	Star* star1 = new Star(Color(DefaultColor::RED, 1.0f), { 0,50.0f * sqrtf(3) - 25 }, 20000, { 0,0 });
	Star* star2 = new Star(Color(DefaultColor::GREEN, 1.0f), { -50,-25 }, 20000, { 0,0 });
	Star* star3 = new Star(Color(DefaultColor::BULE, 1.0f), { 50,-25 }, 20000, { 0,0 });

	gs.addStar(star1);
	gs.addStar(star2);
	gs.addStar(star3);
	gs.setCanCollide(false);
	
	
	/*
	Star* star1 = new Star(Color(DefaultColor::RED, 1.0f), { -100,0 }, 20000, { 0,10 });
	Star* star2 = new Star(Color(DefaultColor::GREEN, 1.0f), { 100,0 }, 20000, { 0,-10 });
	gs.addStar(star1);
	gs.addStar(star2);
	*/

	/*
	Star* sun = new Star(Color(DefaultColor::RED, 1.0f), { 0,0 }, 2000000, {0,0});
	sun->setRemoveable(false);
	sun->setRho(3000);
	gs.addStar(sun);

	float TEMP = displayArea * 2 + 1;
	float massMax = 100000,massMin = 1000;
	float speedMax = 50,speedMin = 20;
	for (int i = 0; i < 500; i++) {
		Color color = Color(rand() / double(RAND_MAX), rand() / double(RAND_MAX), rand() / double(RAND_MAX),1.0f);
		vec2d pos = { fmod(rand(),TEMP) - displayArea ,fmod(rand(),TEMP) - displayArea };
		float mass = fmod(rand(), massMax + massMin + 1) - massMin;
		vec2d vec = { pow(-1,rand()) * fmod(rand(), speedMax + speedMin + 1) - speedMin,pow(-1,rand()) * fmod(rand(), speedMax + speedMin + 1) - speedMin };
		Star* star = new Star(color,pos,mass,vec);
		gs.addStar(star);
	}
	*/
	
	while (!display.windowShouldClose()) {

		display.clear();

		if (!pause) {
			gs.moveAll();
			gs.checkCollision();
		}
		gs.drawAll(display);

		display.swapBuffers();
		display.pollEvents();

		Sleep(1000 / fps);

	}

	return EXIT_SUCCESS;

}

void init() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, "2DGravitySimulate", NULL, NULL);
	if (window == NULL) {
		cerr << "window == NULL" << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cerr << "glad load failure" << endl;
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, keyPress);
	glfwSetMouseButtonCallback(window, mouseClick);

}

void keyPress(GLFWwindow* window, int key, int scancode, int action, int modes) {
	if (action != GLFW_PRESS)
		return;
	switch (key) {
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, GL_TRUE);
		break;
	case GLFW_KEY_SPACE:
		if (!pause)
			pause = true;
		else {
			pause = false;
			Star::flushLastMove();
		}
		break;
	}
}

void mouseClick(GLFWwindow* window, int button, int action, int modes) {
}