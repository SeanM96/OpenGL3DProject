#include "libs.h"
#include "Shader.h"

std::ifstream fs_stream("fragment_core.glsl");
std::string fs_source((std::istreambuf_iterator<char>(fs_stream)),
(std::istreambuf_iterator<char>()));

std::ifstream vs_stream("vertex_core.glsl");
std::string vs_source((std::istreambuf_iterator<char>(vs_stream)),
(std::istreambuf_iterator<char>()));

int main() {
	//INIT GLFW
	glfwInit();

	//CREATE WINDOW
	const int WINDOW_WIDTH = 1920;
	const int WINDOW_HEIGHT = 1080;
	int framebufferWidth = 0;
	int framebufferHeight = 0;

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // FOR MAC OS
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Window", glfwGetPrimaryMonitor(), NULL);
	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	glViewport(0,0,framebufferWidth, framebufferHeight);

	glfwMakeContextCurrent(window);
	
	//INIT GLEW (NEEDS WINDOW AND OPENGL CONTEXT)
	glewExperimental = GL_TRUE;

	//Error Check
	if (glewInit() != GLEW_OK) {
		std::cout << "Error MAIN.cpp GLEW INIT FAILED";
		glfwTerminate();
	}
	else {
		std::cout << "Glew init successful" << "\n";
	}

	Shader *mainShader = new Shader(vs_source.c_str(), fs_source.c_str());

	//MAIN LOOP
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window)) {
		//UPDATE INPUT
		glfwPollEvents();
		//UPDATE

		//DRAW------

		//clear
		glClearColor(1.f,0.f,0.f,1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//draw

		//END DRAW
		glfwSwapBuffers(window);
		glFlush();
	}

	//END OF PROGRAM
	glfwDestroyWindow(window);
	delete mainShader;
	glfwTerminate();

	return 0;
}