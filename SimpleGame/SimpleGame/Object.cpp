
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

	ShooterIndex = -1;
	if (ObjectType == OBJECT_CHARACTER)
	{
		vX = 200.f *(((float)std::rand() / (float)RAND_MAX) - 1.5f);
		vY = 200.f *(((float)std::rand() / (float)RAND_MAX) - 1.5f);

		size = 15;
		color[0] = 1;
		color[1] = 1;
		color[2] = 1;
		color[3] = 1;

		Life = 10;
		Lifetimer = 1000.0f;
	}
	else if (ObjectType == OBJECT_BUILDING)
	{

		size = 80;
		color[0] = 1;
		color[1] = 1;
		color[2] = 0;
		color[3] = 1;

		Life = 500;
		Lifetimer = 500.0f;

		BulletTimer = 0.0f;
	}
	else if (ObjectType == OBJECT_BULLET)
	{
		vX = 600.f *(((float)std::rand() / (float)RAND_MAX) - 1.5f);
		vY = 600.f *(((float)std::rand() / (float)RAND_MAX) - 1.5f);
		
		if (std::rand() % 2 == 1)
			vX = -vX;
		if (std::rand() % 2 == 1)
			vY = -vY;

		size = 7;
		color[0] = 1;
		color[1] = 0;
		color[2] = 0;
		color[3] = 1;

		Life = 20;
		Lifetimer = 500.0f;

		BulletTimer = 0.0f;
	}
<<<<<<< HEAD
	else if (ObjectType == OBJECT_ARROW)
=======
}

//Arrow �����
Object::Object(float x, float y, int Type, int index)
{
	posX = x;
	posY = y;
	ObjectType = Type;

	if (ObjectType == OBJECT_ARROW)
>>>>>>> parent of 4ebcafe... Lecture 7
	{
		vX = 200.f *(((float)std::rand() / (float)RAND_MAX) - 1.5f);
		vY = 200.f *(((float)std::rand() / (float)RAND_MAX) - 1.5f);

		size = 7;
		color[0] = 1;
		color[1] = 0;
		color[2] = 0;
		color[3] = 1;

<<<<<<< HEAD
<<<<<<< HEAD
		Life = 10;
=======
>>>>>>> parent of 4ebcafe... Lecture 7
=======
>>>>>>> parent of 4ebcafe... Lecture 7
		Lifetimer = 500.0f;
	}
}


Object::~Object()
{
}

void Object::Update(float elapsedTime)
{
	float elapsedTimeInSecond = elapsedTime / 1000.f;
	
	BulletTimer += elapsedTimeInSecond;
	
	if (ObjectType != OBJECT_BUILDING)
	{
		Lifetimer -= 0.02f;
		//std::cout << Lifetimer << std::endl;
		posX = posX + vX * elapsedTimeInSecond;
		posY = posY + vY * elapsedTimeInSecond;

		if (posX > 250)
		{
			posX = 250;

			if (ObjectType == OBJECT_BULLET)
			{
				Life = 0.f;
				std::cout << "delete" << std::endl;
			}

			vX = -vX;
		}

		if (posX < -250)
		{
			posX = -250;

			if (ObjectType == OBJECT_BULLET)
			{
				Life = 0.f;
			}

			vX = -vX;
		}

		if (posY > 400)
		{
			posY = 400;

			if (ObjectType == OBJECT_BULLET)
			{
				Life = 0.f;
			}

			vY = -vY;
		}

		if (posY < -400)
		{
			posY = -400;

			if (ObjectType == OBJECT_BULLET)
			{
				Life = 0.f;
			}

			vY = -vY;
		}
	}
	if (ObjectType == OBJECT_BULLET)
	{
		posX = posX + vX * elapsedTimeInSecond;
		posY = posY + vY * elapsedTimeInSecond;

	}
}

float Object::GetTime()
{
	return Lifetimer;
}