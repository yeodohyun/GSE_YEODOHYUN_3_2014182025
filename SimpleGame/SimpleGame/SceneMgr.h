#pragma once
#include "Object.h"

#define MAX_OBJECTS_COUNT 10
class SceneMgr
{
private:

public:
	Object m_objects[MAX_OBJECTS_COUNT];
	int ObjNum = 0;
	SceneMgr();
	~SceneMgr();
	void AddObject(Object obj);
	void Update(); 
	void CollisionTest();
};

