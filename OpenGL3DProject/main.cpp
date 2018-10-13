#include "libs.h"
#include "Shader.h"
#include "Wrapper.h"

std::ifstream fs_stream("fragment_core.glsl");
std::string fs_source((std::istreambuf_iterator<char>(fs_stream)),
(std::istreambuf_iterator<char>()));

std::ifstream vs_stream("vertex_core.glsl");
std::string vs_source((std::istreambuf_iterator<char>(vs_stream)),
(std::istreambuf_iterator<char>()));

void updateInput(GLFWwindow* window) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main() {
	//INIT GLFW
	glfwInit();

	Wrapper mainWrapper = Wrapper();
	Shader *mainShader = new Shader(vs_source.c_str(), fs_source.c_str());

	//MAIN LOOP
	while (!glfwWindowShouldClose(mainWrapper.getWindow())) {
		//UPDATE INPUT
		updateInput(mainWrapper.getWindow());
		glfwPollEvents();
		//UPDATE

		//DRAW------

		//clear
		glClearColor(1.f,0.f,0.f,1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//draw

		//END DRAW
		glfwSwapBuffers(mainWrapper.getWindow());
		glFlush();
	}

	//END OF PROGRAM
	glfwDestroyWindow(mainWrapper.getWindow());
	delete mainShader;
	glfwTerminate();

	return 0;
}