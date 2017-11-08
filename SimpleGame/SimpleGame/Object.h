#pragma once


class Object
{
public:

	float posX, posY;
	float vX, vY;
	int size, color[4];

	int Life;
	float Lifetimer;


	Object();
	Object(float x, float y);
	~Object();
	void Update(float elapsedTime);
	float GetTime();
};

