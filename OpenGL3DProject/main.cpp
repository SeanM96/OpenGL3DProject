#include "libs.h"
#include "Shader.h"
#include "Wrapper.h"

using namespace glm;

std::ifstream fs_stream("fragment_core.glsl");
std::string fs_source((std::istreambuf_iterator<char>(fs_stream)),
(std::istreambuf_iterator<char>()));

std::ifstream vs_stream("vertex_core.glsl");
std::string vs_source((std::istreambuf_iterator<char>(vs_stream)),
(std::istreambuf_iterator<char>()));

 Vertex vertices[] = {
	 //Position					//Colour				//Texcoords			/Normals
	 vec2(0.5f, 0.5f),			vec3(1.f, 0.f, 0.f),	vec2(1.f, 1.f),		vec3(0.f, 0.f, 1.f),//Top Right
	 vec2(0.5f, -0.5f),			vec3(0.f, 1.f, 0.f),	vec2(1.f, 0.f),		vec3(0.f, 0.f, 1.f), //Bottom Right
	 vec2(-0.5f, -0.5f),		vec3(0.f, 0.f, 1.f),	vec2(0.f, 0.f),		vec3(0.f ,0.f, 1.f),//Bottom Left
	 vec2(-0.5f, 0.5f),			vec3(1.f, 1.f, 1.f),	vec2(0.f, 1.f),		vec3(0.f, 0.f, 1.f)//Top Left

};

 unsigned int numOfVertices = sizeof(vertices) / sizeof(Vertex);

 GLuint indices[] = {
	 0,1,3,
	 1,2,3
 };

 unsigned numOfIndices = sizeof(indices) / sizeof(GLint);

void updateInput(GLFWwindow* window, int typeOfPress, vec3& position, vec3& rotation, vec3& scale) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == typeOfPress)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (glfwGetKey(window, GLFW_KEY_W) == typeOfPress)
		position.y += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_A) == typeOfPress)
		position.x -= 0.01f;
	if (glfwGetKey(window, GLFW_KEY_S) == typeOfPress)
		position.y -= 0.01f;
	if (glfwGetKey(window, GLFW_KEY_D) == typeOfPress)
		position.x += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_O) == typeOfPress)
		position.z -= 0.01f;
	if (glfwGetKey(window, GLFW_KEY_P) == typeOfPress)
		position.z += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_UP) == typeOfPress)
		rotation.x -= 2.f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == typeOfPress)
		rotation.x += 2.f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == typeOfPress)
		rotation.y -= 2.f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == typeOfPress)
		rotation.y += 2.f;
	if (glfwGetKey(window, GLFW_KEY_R) == typeOfPress) {
		position = vec3(0.f);
		rotation = vec3(0.f);
		scale = vec3(1.f);
		}
}

int main() {
	//INIT GLFW
	glfwInit();

	Wrapper mainWrapper = Wrapper();
	Shader *mainShader = new Shader(vs_source.c_str(), fs_source.c_str());

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0,2, GL_FLOAT, GL_FALSE, sizeof(Vertex),(GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);

	//TEXTURE INIT
	int image_width = 0;
	int image_height = 0;
	unsigned char* image = SOIL_load_image("images/pusheen.png", &image_width, &image_height, NULL, SOIL_LOAD_RGBA);
	GLuint texture0;
	glGenTextures(1, &texture0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (image) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		std::cout << "IMAGE LOADED";
	}
	else {
		std::cout << "Error loading image";
	}
	//Clean up, needed when stuff done with texture
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);

	//Init matrices

	vec3 position(0.f);
	vec3 rotation(0.f);
	vec3 scale(1.f);
	mat4 ModelMatrix(1.f);

	ModelMatrix = translate(ModelMatrix,position);
	ModelMatrix = rotate(ModelMatrix, radians(rotation.x), vec3(1.f,0.f,0.f));
	ModelMatrix = rotate(ModelMatrix, radians(rotation.y), vec3(0.f, 1.f, 0.f));
	ModelMatrix = rotate(ModelMatrix, radians(rotation.z), vec3(0.f, 0.f, 1.f));
	ModelMatrix = glm::scale(ModelMatrix, scale); //Needs glm as I have a variable called scale

	vec3 camPosition = vec3(0.f,0.f,1.f);
	vec3 worldUp = vec3(0.f, 1.f, 0.f);
	vec3 camFront = vec3(0.f, 0.f, -2.f);
	mat4 ViewMatrix(1.f);
	ViewMatrix = lookAt(camPosition, camPosition + camFront, worldUp);

	float fov = 90.f; //The angle from which the camera goes out
	float nearPlane = 0.1f; //How close the camera can see
	float farPlane = 1000.f; //Draw distance
	mat4 ProjectionMatrix(1.f); //Needs to be first initialised
	ProjectionMatrix = perspective(radians(fov), static_cast<float>(mainWrapper.framebufferWidth) / mainWrapper.framebufferHeight, nearPlane, farPlane); //Camera projection. World moves, camera does not

	//Init Lights
	vec3 lightPos0(0.f, 0.f, 1.f);
	//Init uniforms
	glUseProgram(mainShader->myProgram);
	glUniformMatrix4fv(glGetUniformLocation(mainShader->myProgram, "ModelMatrix"), 1, GL_FALSE, value_ptr(ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(mainShader->myProgram, "ViewMatrix"), 1, GL_FALSE, value_ptr(ViewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(mainShader->myProgram, "ProjectionMatrix"), 1, GL_FALSE, value_ptr(ProjectionMatrix));

	glUniform3fv(glGetUniformLocation(mainShader->myProgram, "lightPos"), 1, value_ptr(lightPos0));

	glUseProgram(0);

	//MAIN LOOP
	while (!glfwWindowShouldClose(mainWrapper.getWindow())) {
		//UPDATE INPUT
		updateInput(mainWrapper.getWindow(), GLFW_PRESS, position, rotation, scale);
		glfwPollEvents();
		//UPDATE

		//DRAW------

		//clear
		glClearColor(0.f,0.f,0.f,1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//draw
		glUseProgram(mainShader->myProgram);
		//Transforms
		mat4 ModelMatrix(1.f);
		ModelMatrix = translate(ModelMatrix, position);
		ModelMatrix = rotate(ModelMatrix, radians(rotation.x), vec3(1.f, 0.f, 0.f));
		ModelMatrix = rotate(ModelMatrix, radians(rotation.y), vec3(0.f, 1.f, 0.f));
		ModelMatrix = rotate(ModelMatrix, radians(rotation.z), vec3(0.f, 0.f, 1.f));
		ModelMatrix = glm::scale(ModelMatrix, scale); //Needs glm as I have a variable called scale
		glUniformMatrix4fv(glGetUniformLocation(mainShader->myProgram, "ModelMatrix"), 1, GL_FALSE, value_ptr(ModelMatrix));
		glfwGetFramebufferSize(mainWrapper.getWindow(), &mainWrapper.framebufferWidth, &mainWrapper.framebufferHeight);

		ProjectionMatrix = mat4(1.f);
		ProjectionMatrix = perspective(radians(fov), static_cast<float>(mainWrapper.framebufferWidth) / mainWrapper.framebufferHeight, nearPlane, farPlane); //This is so the image doesnt stretch when window is resized. Same AR returned.
		glUniformMatrix4fv(glGetUniformLocation(mainShader->myProgram, "ProjectionMatrix"), 1, GL_FALSE, value_ptr(ProjectionMatrix));

		//activate texture
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, texture0);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, numOfIndices, GL_UNSIGNED_INT, 0);
		
		//END DRAW
		glfwSwapBuffers(mainWrapper.getWindow());
		glFlush();

		glBindVertexArray(0);
		glUseProgram(0);
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D,0);
	}

	//END OF PROGRAM
	glfwDestroyWindow(mainWrapper.getWindow());
	delete mainShader;
	glfwTerminate();

	return 0;
}