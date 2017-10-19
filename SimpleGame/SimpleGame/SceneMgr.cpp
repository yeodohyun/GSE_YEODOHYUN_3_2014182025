#include "stdafx.h"
#include "SceneMgr.h"
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
		std::cout << "Not Enough Space!!!" << std::endl;
}

void SceneMgr::Update() {
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		m_objects[i].Update();

	}
}