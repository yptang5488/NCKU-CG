//#define GLEW_STATIC
//#include <gl\glew.h>
#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"
#include "Shader.h"
#include "camera.h"
#include "model.h"

#include <stdio.h>

const GLuint WIDTH = 800, HEIGHT = 600;
GLuint texture, texture2;
GLuint VBO, VAO;

bool mouse_flag = true;
bool mouse_clicked = false;
bool keys_pressed[1024] = {false};


Camera camera(glm::vec3(0.0f, 3.0f, 10.0f));
GLfloat angle_x = 0.0f;
GLfloat angle_y = 0.0f;
GLfloat angle_speed = 0.25f;
GLfloat lastX = 0, lastY = 0;

bool run_animation = false;

// Vertex
GLfloat vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
	glm::vec3( 0.0f,  0.0f,  0.0f),
	glm::vec3( 2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3( 2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3( 1.3f, -2.0f, -2.5f),
	glm::vec3( 1.5f,  2.0f, -2.5f),
	glm::vec3( 1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

float blend = 0.0f;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key >= 0 && key < 1024) {
		// cout << "key press " << key << endl;
        if (action == GLFW_PRESS){
            keys_pressed[key] = true;
        }
        if (action == GLFW_RELEASE) {
            keys_pressed[key] = false;
        }
    }

	if ((keys_pressed[GLFW_KEY_SPACE])) {
		if (run_animation)
			run_animation = false;
		else
			run_animation = true;
	}
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		mouse_clicked = true;
	} else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		mouse_clicked = false;
		mouse_flag = true;
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

void cube_setup(){
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// VAO
	glBindVertexArray(VAO);

	// VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), static_cast<GLvoid *>(nullptr));
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	
	glBindVertexArray(0);
}

void cube_render(int width, int height, Shader shader){
	// use Transform
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(45.0f, (float)width / height, 0.1f, 100.0f);

	GLuint modelLoc = glGetUniformLocation(shader.ID, "model");
	GLuint viewLoc = glGetUniformLocation(shader.ID, "view");
	GLuint projectionLoc = glGetUniformLocation(shader.ID, "projection");
	
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(VAO);

	glm::mat4 model = glm::mat4(1.0f);
	// GLfloat angle = glm::radians((GLfloat)glfwGetTime() * 20.0f * (i+1));
	model = glm::rotate(model, (GLfloat)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);
}

void model_render(Model* model, Shader shader){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float time = glfwGetTime();
	float radius = 8.0f;
	glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 10.0f);

	GLuint modelLoc = glGetUniformLocation(shader.ID, "model");
	GLuint projLoc = glGetUniformLocation(shader.ID, "projection");
	GLuint viewLoc = glGetUniformLocation(shader.ID, "view");
	GLuint viewPosLoc = glGetUniformLocation(shader.ID, "viewPos");
	GLuint lightPosLoc = glGetUniformLocation(shader.ID, "lightPos");
	
	glUniform3fv(viewPosLoc, 1, glm::value_ptr(camera.GetPosition()));
	glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));

	glm::mat4 projection = glm::perspective(camera.GetZoom(), 800.0f/600, 1.0f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();
	
	// glm::mat4 view = glm::mat4(1.0f);
	// glm::mat4 projection = glm::mat4(1.0f);

	// view = glm::translate(view, glm::vec3(0.0f, 0.0f, -30.0f));
	// view = glm::rotate(view, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	// projection = glm::perspective(45.0f, (float)800 / 600, 0.1f, 100.0f);
	// 
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 eye(1.0f);
	glm::mat4 modelPosition;

	modelPosition = glm::rotate(eye, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(eye, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(eye, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	modelPosition = glm::rotate(modelPosition, glm::radians(angle_x * angle_speed), glm::vec3(0.0f, 0.0f, 1.0f));
	modelPosition = glm::rotate(modelPosition, glm::radians(angle_y * angle_speed), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelPosition));

	// glm::mat4 modelmat = glm::mat4(1.0f);
	// glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelmat));

	model->update(keys_pressed);
	model->render(shader.ID, run_animation);
}


int main(int argc, char* argv[])
{
	memset(keys_pressed, false, 1024);
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// glfwSwapInterval(1);

	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glewExperimental = GL_TRUE;
	glewInit();

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);

	// Shader CubeShader = Shader("default.vs", "default.frag");
	Shader ModelShader = Shader("model.vs", "model.frag");
	Model *model = new Model("model.dae");
	model->initBoneLoc(ModelShader.ID);

	// cube_setup();

	float last, start;
	last = start = glfwGetTime();
	int fps = 0;

	while (!glfwWindowShouldClose(window)){
		double xPos, yPos;

		if (mouse_clicked) {
			glfwGetCursorPos(window, &xPos, &yPos);

			if (mouse_flag) {
				lastX = xPos;
				lastY = yPos;
				mouse_flag = false;
			}
			
			GLfloat xOffset = lastX - xPos;
			GLfloat yOffset = yPos - lastY;

			lastX = xPos;
			lastY = yPos;
			
			angle_x += xOffset;
			angle_y += yOffset;
		}

		// set color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		/* model */
		glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT);
		ModelShader.Use();
		model_render(model, ModelShader);
		glPopAttrib();

		/* cube */
		// glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT);
		// CubeShader.Use();
		// cube_render(width, height, CubeShader);
		// glPopAttrib();

		glfwSwapBuffers(window);
		glfwPollEvents();
		fps++;
		if (glfwGetTime() - last > 1.0)
		{
			std::cout << (double)fps / (glfwGetTime() - last) << std::endl;
			fps = 0;
			last = glfwGetTime();
		}
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}