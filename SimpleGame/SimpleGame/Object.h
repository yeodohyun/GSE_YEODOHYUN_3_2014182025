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

	float ArrowTimer;
	int ShooterIndex;

	unsigned int m_texCharacter;

	Object();
	Object(float x, float y, int Type);
	Object(float x, float y, int Type, int index, int life);
	~Object();
	void Update(float elapsedTime);
	float GetTime();
};

