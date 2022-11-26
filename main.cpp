// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


// Include GLEW
#include "dependente\glew\glew.h"

// Include GLFW
#include "dependente\glfw\glfw3.h"

// Include GLM
#include "dependente\glm\glm.hpp"
#include "dependente\glm\gtc\matrix_transform.hpp"
#include "dependente\glm\gtc\type_ptr.hpp"

#include "shader.hpp"
#include <Windows.h>
#include <MMSystem.h>
//variables
GLFWwindow* window;
const int width = 1024, height = 768;
bool r = false;
//level number
int levelNum = 1;
int hearts = 3;

//asteroids speed
float speed = 0.00005f;
// ship initial position 
glm::vec3 shipPos(0.0f, -0.8f, 0.0f);

glm::vec3 shipColor(1.0f);
//bullet initial position
float x = shipPos.x;
float y = shipPos.y + 0.2f;
glm::vec3 bulletPos;


void window_callback(GLFWwindow* window, int new_width, int new_height)
{
	glViewport(0, 0, new_width, new_height);
}

//asteroids
float vertices[] = {
	-0.05f, -0.08f, 0.0f,
	-0.05f, 0.07f, 0.0f,
	0.04f,  0.08f, 0.0f,
	0.06f, -0.07f, 0.0f,
	0.08f, 0.0f, 0.0f,
	-0.08f, 0.0f, 0.0f,
};

unsigned int indices[] = {
		0,1,2,
		3,0,2,
		3,4,2,
		5,1,0
};

//ship
float vertices2[] = {
	0.00f, 0.09f, 0.0f,  // top
	-0.08f,  -0.05f, 0.0f,  //  right
	0.08f, -0.05f, 0.0f,  //  left
	-0.08f,  -0.08f, 0.0f,  //  right top 
	0.08f, -0.08f, 0.0f,  //  left top
	0.00f,  -0.05f, 0.0f,  // top
};


unsigned int indices2[] = {
	0,1,2,
	1,3,5,
	5,4,2
};
//bullet
float vertices3[] = {
		0.005f,  0.04f, 0.0f,  // top right
		0.005f, -0.04f, 0.0f,  // bottom right
		-0.005f, -0.04f, 0.0f,  // bottom left
		-0.005f,  0.04f, 0.0f   // top left 
};


unsigned int indices3[] = {  // note that we start from 0!
	0, 1, 3,  // first Triangle
	1, 2, 3   // second Triangle
};
//health hearts
float vertices4[] = {
	0.00f, -0.08f, 0.0f,  // top
	-0.08f,  0.05f, 0.0f,  //  right
	0.08f, 0.05f, 0.0f,  //  left
	-0.08f,  0.08f, 0.0f,  //  right top 
	0.08f, 0.08f, 0.0f,  //  left top
	0.00f,  0.05f, 0.0f,  // middle
	-0.04f,  0.1f, 0.0f,  //  right top top
	0.04f, 0.1f, 0.0f,  //  left top top


};


unsigned int indices4[] = {
	0,1,2,
	1,3,5,
	5,4,2,
	3,6,5,
	5,7,4

};
glm::vec3 health_positions[] = {
	glm::vec3(-0.9f, 0.9f, 0.0f),
	glm::vec3(-0.82f, 0.9f, 0.0f),
	glm::vec3(-0.74f, 0.9f, 0.0f),


};

glm::vec3 positions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(0.5f,  0.5f, 0.0f),
	glm::vec3(-0.3f, 0.22f, 0.0f),
	glm::vec3(-0.8f, 0.7f, -0.0f),
	glm::vec3(0.24f, 0.6f, 0.0f),
	glm::vec3(-0.55f,  0.5f, 0.0f),
	glm::vec3(0.74f, 0.3f, 0.0f),
	glm::vec3(0.15f,  0.4f, 0.0f),
	glm::vec3(0.78f,  0.7f, 0.0f),

	glm::vec3(0.0f,  0.9f,  0.0f),
	glm::vec3(0.21f,  1.4f, 0.0f),
	glm::vec3(-0.36f, 1.3f, 0.0f),
	glm::vec3(0.5f, 1.6f, -0.0f),
	glm::vec3(0.34f, 1.4f, 0.0f),
	glm::vec3(-0.54f,  1.2f, 0.0f),
	glm::vec3(-0.76f, 1.7f, 0.0f),
	
	glm::vec3(2.0f,  2.1f, 0)

};
glm::vec3 sizes[] = {
	glm::vec3(1.032f,  1.053f, 0.0f),
	glm::vec3(1.133f, 1.542f, 0),
	glm::vec3(1.834f, 1.674f, 0.0),
	glm::vec3(1.963f, 1.912f, 0.0),
	glm::vec3(0.912f, 0.943f, 0.0),
	glm::vec3(1.312f, 1.443f, 0.0),
	glm::vec3(1.732f,  1.653f, 0.0f),
	glm::vec3(1.026f,  0.999f, 0.0f),
	glm::vec3(1.026f,  1.2f, 0.0f),
	glm::vec3(0.999f,  1.153f, 0.0f),
	glm::vec3(1.032f,  1.053f, 0.0f),
	glm::vec3(1.133f, 1.542f, 0),
	glm::vec3(1.834f, 1.674f, 0.0),
	glm::vec3(1.463f, 1.312f, 0.0),
	glm::vec3(0.912f, 0.943f, 0.0),
	glm::vec3(1.312f, 1.443f, 0.0),
	glm::vec3(1.732f,  1.653f, 0.0f),
	glm::vec3(1.026f,  0.999f, 0.0f),
	glm::vec3(1.026f,  1.2f, 0.0f),
	glm::vec3(0.999f,  1.153f, 0.0f),

};
//get random float in range
float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}
//rounding values
float roundd(float var)
{
	float value = (int)(var * 10 + .4);
	return (float)value / 10;
}

// to respawn the asteroids after the last asteroid pass the lower border
void reset() {
	// give random y values for the asteroid positions
	for (int i = 0; i < 17; i++) {
		float r = RandomFloat(0.0, 1.0);
		float r2 = RandomFloat(1.0, 2.0);
		if(i<=8){
		positions[i].y = r;
		} 
		if (i > 8) {
			positions[i].y = r2;
		}
	}
	//we use the last asteroid the check the end of the wave,
	// giving it a large x value to keep it out of the screen so the user doesn't destroy it, 
	//whilst making sure it has biggest y value so it comes last.
	positions[16] = glm::vec3(2.0f, 2.1f, 0);

}
// to move the ship and restrict it to our windows' borders
void move(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		if (shipPos.y < 0.887985) {
			shipPos.y = shipPos.y + 0.001f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		if (shipPos.y > -0.887985) {
			shipPos.y = shipPos.y - 0.001f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		if (shipPos.x > -0.925) {
			shipPos.x = shipPos.x - 0.001f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		if(shipPos.x < 0.925) {
		shipPos.x = shipPos.x + 0.001f;
		}
	}

}
// to shoot bullet, we use the boolean value to check if the mouse button is clicked in our main, if so then shoot a bullet
void mouse_button_callback(GLFWwindow* window, int button, int
	action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		r = true;
		PlaySound("bullet.wav", NULL, SND_ASYNC | SND_FILENAME);

	}
}



int main(void)
{	
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(width, height, "3D demo", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window.");
		getchar();
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	//specify the size of the rendering window
	glViewport(0, 0, width, height);

	// Dark blue background

	glClearColor(0.0f, 0.0f, 0.1f, 0.0f);
	

	glClear(GL_COLOR_BUFFER_BIT);

	// Create and compile our GLSL program from the shaders
	// More about this in the following labs
	GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");



	// A Vertex Array Object (VAO) is an object which contains one or more Vertex Buffer Objects and is designed to store 
	// the information for a complete rendered object.
	 
	//The asteroids
	GLuint vbo, vao, ibo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//set attribute pointers
	glVertexAttribPointer(
		0,                  // attribute 0, must match the layout in the shader.
		3,                  // size of each attribute
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		3 * sizeof(float),                  // stride
		(void*)0            // array buffer offset
	);
	glEnableVertexAttribArray(0);

	// The ship
	GLuint vbo2, vao2, ibo2;
	glGenVertexArrays(1, &vao2);
	glGenBuffers(1, &vbo2);
	glGenBuffers(1, &ibo2);

	glBindVertexArray(vao2);

	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

	//set attribute pointers
	glVertexAttribPointer(
		0,                  // attribute 0, must match the layout in the shader.
		3,                  // size of each attribute
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		3 * sizeof(float),                  // stride
		(void*)0            // array buffer offset
	);
	glEnableVertexAttribArray(0);
	
	// The bullet
	GLuint vbo3, vao3, ibo3;

	glGenVertexArrays(1, &vao3);
	glGenBuffers(1, &vbo3);
	glGenBuffers(1, &ibo3);

	glBindVertexArray(vao3);

	glBindBuffer(GL_ARRAY_BUFFER, vbo3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices3), indices3, GL_STATIC_DRAW);

	//set attribute pointers
	glVertexAttribPointer(
		0,                  // attribute 0, must match the layout in the shader.
		3,                  // size of each attribute
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		3 * sizeof(float),                  // stride
		(void*)0            // array buffer offset
	);
	glEnableVertexAttribArray(0);

	// hearts
	GLuint vbo4, vao4, ibo4;

	glGenVertexArrays(1, &vao4);
	glGenBuffers(1, &vbo4);
	glGenBuffers(1, &ibo4);

	glBindVertexArray(vao4);

	glBindBuffer(GL_ARRAY_BUFFER, vbo4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices4), vertices4, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo4);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices4), indices4, GL_STATIC_DRAW);

	//set attribute pointers
	glVertexAttribPointer(
		0,                  // attribute 0, must match the layout in the shader.
		3,                  // size of each attribute
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		3 * sizeof(float),                  // stride
		(void*)0            // array buffer offset
	);
	glEnableVertexAttribArray(0);

	
	glfwSetFramebufferSizeCallback(window, window_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);


	// Check if the window was closed
	while (!glfwWindowShouldClose(window))
	{

		// Swap buffers
		glfwSwapBuffers(window);
		
		// Check for events
		glfwPollEvents();

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);
		move(window);

		int i=0;
		// if the last asteroid passes the lower border, reset positions and respawn the asteroids
		if (positions[16].y < -0.887985 || shipPos.y > 0.8) {
			shipPos.x = 0.0f;
			shipPos.y = -0.8f;
			reset();
			levelNum++;
			// increase the speed of asteroids according to the level
			if (levelNum <= 5)
			{
				speed = speed + 0.00005f;

			}
			else if (levelNum > 5) {
				speed = speed + 0.0003f;

			}
			std::cout << "Level: " << levelNum << std::endl;

		}
		//draw asteroids	
		while(i<17){
			glm::mat4 model1;

			model1 = glm::translate(model1, positions[i]);
			float angle;
			if(i%2==0){
				angle = (float)glfwGetTime() * 20;
			}
			else {
				angle = -(float)glfwGetTime() * 20;
			}
			model1 = glm::rotate(model1, angle, glm::vec3(0.0f, 0.0f, 1.0f));
			model1 = glm::scale(model1, sizes[i]);

			unsigned int transformloc = glGetUniformLocation(programID, "transform");
			glUniformMatrix4fv(transformloc, 1, GL_FALSE, glm::value_ptr(model1));

			unsigned int transformloc2 = glGetUniformLocation(programID, "color");
			if (levelNum <= 5)
			{
				glUniform4fv(transformloc2, 1, glm::value_ptr(glm::vec3(0.6f, 0.2f, 0.2)));
			}
			if (levelNum > 5)
			{
				glUniform4fv(transformloc2, 1, glm::value_ptr(glm::vec3(1.0f, 0.6f, 0.2)));

			}
			//bind vao
			glBindVertexArray(vao);
			glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

			//move the asteroids towards the lower border
			positions[i].y = positions[i].y - speed;
			
		
			i++;
			
			
		}
		
		//draw ship
		glm::mat4 model;
		
		model = glm::translate(model, shipPos);

		unsigned int transformLoc = glGetUniformLocation(programID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));

		unsigned int transformLoc2 = glGetUniformLocation(programID, "color");
		glUniform4fv(transformLoc2, 1, glm::value_ptr(shipColor));
		glBindVertexArray(vao2);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		//collisions
		for (int i = 0; i < 17; i++) {
			//if ship and asteroid collide restart the game.
			if ((roundd(positions[i].x) == roundd(shipPos.x)) && (roundd(positions[i].y) == roundd(shipPos.y))) {
				shipPos.x = 0.0f;
				shipPos.y = -0.8f;
				reset();
				if (levelNum <= 5) {
					hearts--;
				}
				else if (levelNum > 5) {
					hearts = hearts - 2;
				}
			}
		}
		//if all health is depleted, restart game
		if (hearts <= 0) {
			speed = 0.00005f;
			levelNum = 1;
			std::cout << "You Lost! Try again." << std::endl;
			std::cout << "Level: " << levelNum << std::endl;

			hearts = 3;
		}
		// make sure bullet comes out of bullet, but doesn't follow it, that's why it takes the position when the bullet isn't drawn
		if (r == false) {
			bulletPos.x = shipPos.x;
		}
		// draw bullet if the mouse button was clicked
		if(r==true){
		glm::mat4 trans(1.0f);
		trans = glm::translate(glm::mat4(1.0f), bulletPos);
		// move the bullet upwards by changing its y position
		bulletPos.y = bulletPos.y + 0.002f;

		unsigned int transformLoc3 = glGetUniformLocation(programID, "transform");
		glUniformMatrix4fv(transformLoc3, 1, GL_FALSE, glm::value_ptr(trans));

		unsigned int transformLoc4 = glGetUniformLocation(programID, "color");
		glm::vec3 color = glm::vec3(1.0f, 0, 0.4f);
		glUniform4fv(transformLoc4, 1, glm::value_ptr(color));
		glBindVertexArray(vao3);

		//when the bullet passes the upper border, reset the bool value and bullet position
		if (bulletPos.y > 0.887985) {
			r = false;
			bulletPos.y = shipPos.y + 0.2f;
		}
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//bullet Collisions;
		for (int i = 0; i < 17; i++) {
			// if bullet and asteroid collide, reset the bullet position, then move the asteroid out of the screen (aka destroy it)
			if ((roundd(positions[i].x) == roundd(bulletPos.x)) && (roundd(positions[i].y) == roundd(bulletPos.y))) {
				//reset bullet position
				r = false;
				bulletPos.y = shipPos.y + 0.2f;
				//move asteroids out of view
				positions[i].y = 4.0f;
				std::cout << "kill! " << std::endl;

				}
			}
		}

		//draw health hearts
		for (int i = 0; i < hearts; i++) {
			glm::mat4 model4;

			model4 = glm::translate(model4, health_positions[i]);
			model4 = glm::scale(model4, glm::vec3(0.4f, 0.4f, 0.0f));

			unsigned int transformLoc = glGetUniformLocation(programID, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model4));

			unsigned int transformLoc2 = glGetUniformLocation(programID, "color");
			glUniform4fv(transformLoc2, 1, glm::value_ptr(glm::vec3(0.9f, 0.1f, 0.4)));
			glBindVertexArray(vao4);
			glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);
		}






	}
	
	// Cleanup VBO
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	glDeleteVertexArrays(1, &ibo);
	glDeleteBuffers(1, &vbo2);
	glDeleteVertexArrays(1, &vao2);
	glDeleteVertexArrays(1, &ibo2);
	glDeleteBuffers(1, &vbo3);
	glDeleteVertexArrays(1, &vao3);
	glDeleteVertexArrays(1, &ibo3);
	glDeleteBuffers(1, &vbo4);
	glDeleteVertexArrays(1, &vao4);
	glDeleteVertexArrays(1, &ibo4);

	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}


