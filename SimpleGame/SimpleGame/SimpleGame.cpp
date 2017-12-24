/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include "windows.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"
#include "Object.h"
#include "SceneMgr.h"

using namespace std;


SceneMgr *g_SceneMgr = NULL;


DWORD prevTime = 0;

float PlayerTimer = 0;
bool InputLButton = false;
int Input = 1;
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	DWORD currTime = timeGetTime();
	DWORD elapsedTime = currTime - prevTime;
	prevTime = currTime;

	// Renderer Test
	g_SceneMgr->UpateSceneMgr((float)elapsedTime);
	g_SceneMgr->DrawAllObjects();

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		if (-(y - 400) < 0 && -(y - 400) > -350 && x - 300>-250 && x - 300<150)
		{
			cout << Input << endl;
			g_SceneMgr->MouseClick(x - 300, -(y - 400));
		}
	}

	std::cout << "button" << button << "state : " << state << "x :" << x << "y: " << y << std::endl;
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	switch (key) {
	case '1':
		std::cout << "1" << std::endl;
		g_SceneMgr->Select = 1;
		Input = 1;
		break;
	case '2':
		std::cout << "2" << std::endl;
		g_SceneMgr->Select = 2;
		Input = 2;
		break;
	case '3':
		std::cout << "3" << std::endl;
		g_SceneMgr->Select = 3;
		Input = 3;
		break;
	case '4':
		std::cout << "4" << std::endl;
		g_SceneMgr->Select = 4;
		Input = 4;
		break;
	}
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
	glutInitWindowSize(600, 800);
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

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	g_SceneMgr = new SceneMgr(600, 800);

	prevTime = timeGetTime();

	glutMainLoop();

	delete g_SceneMgr;

    return 0;
}

