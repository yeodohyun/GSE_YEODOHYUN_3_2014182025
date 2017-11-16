#pragma once

enum {
	OBJECT_CHARACTER = 1,
	OBJECT_BUILDING = 2,
	OBJECT_BULLET = 3,
	OBJECT_ARROW = 4
};

class Object
{
public:

	float posX, posY;
	float vX, vY;
	int size, color[4];

	int Life;
	float Lifetimer;

	int ObjectType;

	float BulletTimer;

<<<<<<< HEAD
	Object();
	Object(float x, float y, int Type);
=======
	float ArrowTimer;
	int ShooterIndex;

	int Team;

	Object();
	Object(float x, float y, int Type);
	Object(float x, float y, int Type, int index);
>>>>>>> parent of 4ebcafe... Lecture 7
	~Object();
	void Update(float elapsedTime);
	float GetTime();
};

