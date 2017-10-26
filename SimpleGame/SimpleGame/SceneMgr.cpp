#include "stdafx.h"
#include "SceneMgr.h"
#include "Renderer.h"
#include<iostream>


SceneMgr::SceneMgr()
{
}


SceneMgr::~SceneMgr()
{
}

void SceneMgr::AddObject(Object obj) {
	if (MAX_OBJECTS_COUNT > ObjNum) {
		m_objects[ObjNum] = obj;
		ObjNum++;
	}
	else
		std::cout << "²Ë Âü." << std::endl;
}

void SceneMgr::Update() {
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) 
	{
		m_objects[i].Update();
	}
}

void SceneMgr::CollisionTest() {

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		for (int j = 0; j < MAX_OBJECTS_COUNT; j++)
		{
			if (abs(m_objects[i].x - m_objects[j].x) <= 10 && abs(m_objects[i].y - m_objects[j].y) <= 10)
			{
				m_objects[i].g = 0;
				m_objects[i].b = 0;
				m_objects[j].g = 0;
				m_objects[j].b = 0;
			}
			else
			{
				m_objects[i].g = 255;
				m_objects[i].b = 255;
				m_objects[j].g = 255;
				m_objects[j].b = 255;
			}
		}

	}
}
