#pragma once
#include "Shaders.hpp"
#include "Utils.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "View.hpp"
#include "SceneObject.hpp"
#include "Scene.hpp"
class MainApplication {
    public:
	Scene *scene;
	int width = 200;
	int height = 200;

	bool initGlew()
	{
		glewExperimental = true;
		if (glewInit() != GLEW_OK) {
			fprintf(stderr, "Failed to initialize GLEW\n");
			return false;
		}
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glEnable(GL_DEPTH_TEST);
		// glEnable(GL_CULL_FACE);
		glDepthFunc(GL_LESS);
		return true;
	}

	GLFWwindow *initializeWindow()
	{
		if (!glfwInit()) {
			return nullptr;
		}
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		GLFWwindow *window = glfwCreateWindow(width, height,
						      "Raytracer", NULL, NULL);
		glfwMakeContextCurrent(window);
		glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
		return window;
	}

	int initApp()
	{
		// INIT GLFW
		GLFWwindow *window = initializeWindow();

		if (window == nullptr) {
			fprintf(stderr, "Failed to open GLFW window\n");
			glfwTerminate();
			return -1;
		}

		// INIT GLEW
		if (!initGlew()) {
			fprintf(stderr, "Failed to initialize GLEW\n");
			glfwTerminate();
			return -1;
		}

		// INITIAL SETUP
		buildScene(window);

		// START LOOP
		mainLoop(window);
		return 0;
	}

	void buildScene(GLFWwindow *win)
	{
		Camera *cam = new Camera(&width, &height, win);
		scene = new Scene(cam);
		scene->build();
	}

	void mainLoop(GLFWwindow *window)
	{
		do {
			loopCycle(window);
		} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			 glfwWindowShouldClose(window) == 0);
		cleanup();
	}

	void cleanup()
	{
		delete scene;
		glfwTerminate();
	}

	void loopCycle(GLFWwindow *window)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		scene->draw();
		scene->camera->updateFrame();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
};
