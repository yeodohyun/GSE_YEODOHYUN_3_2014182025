
#include "stdafx.h"
#include "Object.h"
#include "Renderer.h"


Object::Object()
{
}

Object::Object(float x, float y, int Type)
{
	posX = x;
	posY = y;
	ObjectType = Type;


	if (ObjectType == OBJECT_CHARACTER)
	{
		vX = 200.f *(((float)std::rand() / (float)RAND_MAX) - 1.5f);
		vY = 200.f *(((float)std::rand() / (float)RAND_MAX) - 1.5f);

		size = 20;
		color[0] = 1;
		color[1] = 1;
		color[2] = 1;
		color[3] = 1;

		Life = 10;
		Lifetimer = 500.0f;
	}
	if (ObjectType == OBJECT_BUILDING)
	{

		size = 100;
		color[0] = 1;
		color[1] = 1;
		color[2] = 0;
		color[3] = 1;

		Life = 500;
		Lifetimer = 500.0f;
	}
	if (ObjectType == OBJECT_BULLET)
	{
		vX = 200.f *(((float)std::rand() / (float)RAND_MAX) - 1.5f);
		vY = 200.f *(((float)std::rand() / (float)RAND_MAX) - 1.5f);

		size = 10;
		color[0] = 1;
		color[1] = 0;
		color[2] = 0;
		color[3] = 1;

		Life = 20;
		Lifetimer = 500.0f;
	}
}


Object::~Object()
{
}

void Object::Update(float elapsedTime)
{
	float elapsedTimeInSecond = elapsedTime / 1000.f;

	if (ObjectType == OBJECT_CHARACTER)
	{
		Lifetimer -= 0.05f;
		//std::cout << Lifetimer << std::endl;
		posX = posX + vX * elapsedTimeInSecond;
		posY = posY + vY * elapsedTimeInSecond;

		if (posX > 250)
		{
			posX = 250;
			vX = -vX;
		}

		if (posX < -250)
		{
			posX = -250;
			vX = -vX;
		}

		if (posY > 250)
		{
			posY = 250;
			vY = -vY;
		}

		if (posY < -250)
		{
			posY = -250;
			vY = -vY;
		}
	}
}

float Object::GetTime()
{
	return Lifetimer;
}