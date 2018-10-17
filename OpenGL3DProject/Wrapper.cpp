#include "Wrapper.h"
#include "libs.h"


Wrapper::Wrapper()
{
	CreateWindow(1920, 1080, 0, 0);
	AddOptions();
	ErrorCheck();
}


Wrapper::~Wrapper()
{
}

void Wrapper::CreateWindow(int WINDOW_WIDTH, int WINDOW_HEIGHT,int frameBufferWidth, int frameBufferHeight) {

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Window", glfwGetPrimaryMonitor(), NULL);
	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
	glViewport(0, 0, frameBufferWidth, frameBufferHeight);

	glfwMakeContextCurrent(window);
}
//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // FOR MAC OS

GLFWwindow* Wrapper::getWindow() {
	return glfwGetCurrentContext();
}

void Wrapper::AddOptions() {
	//OPENGL OPTIONS
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE); //Cull means to remove if we can't see it
	glCullFace(GL_BACK); //This is what we are determining we can't see
	glFrontFace(GL_CW); //Front face counter-clock wise

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC0_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	//INIT GLEW (NEEDS WINDOW AND OPENGL CONTEXT)
	glewExperimental = GL_TRUE;

}

void Wrapper::ErrorCheck() {
	if (glewInit() != GLEW_OK) {
		std::cout << "Error MAIN.cpp GLEW INIT FAILED";
		glfwTerminate();
	}
	else {
		std::cout << "Glew init successful" << "\n";
	}
}
//Error Check
