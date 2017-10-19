/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include <vector>

#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "Renderer.h"
#include "Object.h"
#include "SceneMgr.h"
using namespace std;
Renderer *g_Renderer = NULL;


SceneMgr SMgr;
//Object object;
std::vector<Object> Obj;

void CheckBox(Object ob1, Object ob2) {
	if (ob1.x - (ob1.size / 2) < ob2.x + (ob2.size / 2) && ob1.x + (ob1.size / 2) > ob2.x - (ob2.size / 2) && ob1.y - (ob1.size / 2) < ob2.y + (ob2.size / 2) && ob1.y + (ob1.size / 2) > ob2.y - (ob2.size / 2)) {
		ob1.g = 0;
		ob1.b = 0;
		ob2.g = 0;
		ob2.b = 0;
	}
	else {
		ob1.g = 255;
		ob1.b = 255;
		ob2.g = 255;
		ob2.b = 255;
	}
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	//// Renderer Test
	////g_Renderer->DrawSolidRect(0, 0, 0, 4, 1, 0, 1, 1);
	//object.SetVector(0.07, 0.12, 0);

	//g_Renderer->DrawSolidRect(object.x, object.y, object.z, object.size, object.r, object.g, object.b, object.a);

	//for (auto data : Obj) {
	//	g_Renderer->DrawSolidRect(data.x, data.y, data.z, data.size, data.r, data.g, data.b, data.a);
	//}

	for (auto data : SMgr.m_objects) {
		g_Renderer->DrawSolidRect(data.x, data.y, data.z, data.size, data.r, data.g, data.b, data.a);
	}
	glutSwapBuffers();
}

void Idle(void)
{
	//object.Update();
	
	//for (auto i = Obj.begin(); i < Obj.end(); ++i) {
	//	i->Update();
	//}

	//SMgr.Update();

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {

		for (int j = 0; j < MAX_OBJECTS_COUNT; j++) {
			CheckBox(SMgr.m_objects[i], SMgr.m_objects[j]);
		}
	}
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	//state 0 = keydown, state 1= keyup
	if (state == 1) {
		Object ob(x-250,-(y-250));
		ob.SetVector(0.05, 0.02, 0);
		SMgr.AddObject(ob);
		//Obj.push_back(ob);
	}
	std::cout <<"button"<<button<<"state : "<<state<< "x :" << x << "y: " << y << std::endl;
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;

    return 0;
}

