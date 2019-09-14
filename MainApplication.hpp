#pragma once
#include <GL/glew.h>
#include "src/core/G_Scene.hpp"
#include "src/core/G_Shader.hpp"
#include "src/core/G_Camera.hpp"
#include "src/core/G_Light.hpp"
#include "src/core/G_Camera_Rig.hpp"
#include "src/geometry/G_Mesh.hpp"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
class MainApplication {
    public:
	G_Scene *scene;
	int width = 1024;
	int height = 768;
  G_Camera_Rig *rig;

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
		G_Camera *cam = new G_Camera(width, height);
    G_Light *light = new G_Light(vec3(2, 0, 2), vec3(-2, 0, -1), vec3(1, 0.45,0));
    // cam->position = vec3(0,0,-5);
    // cam->look = vec3(0,0,0);
    rig = new G_Orbit_Camera(cam);
		scene = new G_Scene(cam, light);
    auto blueShader = new G_ColorShader(vec3(1,1,1));
    // auto blueShader = new G_TextureShader(string("textures/uvtemplate.tga").c_str());
    // auto redShader = new G_TextureShader(string("textures/uvtemplate.tga").c_str());
    // auto box = new G_Box_Mesh(vec3(0,0,0), 2.0f, 0.5f, 2.0f);
    auto box2 = new G_ObjMesh(string("objects/monkey.obj").c_str());
    // auto obj = new G_Object(blueShader, box);
    auto obj2 = new G_Object(blueShader, box2);
    // obj2->setPosition(vec3(-0.5,1,-0.5));
    // scene->add_object(obj);
    scene->add_object(obj2);
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
    rig->update_frame(window);
		scene->draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
};
