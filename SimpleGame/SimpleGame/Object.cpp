
#include "stdafx.h"
#include "Object.h"
#include "Renderer.h"

Object::Object()
{
}

Object::Object(float x, float y, int Type, int team)
{
	posX = x;
	posY = y;
	ObjectType = Type;
	Team = team;

	if (ObjectType == OBJECT_CHARACTER)
	{
		vX = 100.f *(((float)std::rand() / (float)RAND_MAX) - 1.5f);
		vY = 100.f *(((float)std::rand() / (float)RAND_MAX) - 1.5f);

		size = 30;

		if (Team == 1)
		{
			color[0] = 1;
			color[1] = 0;
			color[2] = 0;
			color[3] = 1;
		}
		else if (Team == 2)
		{
			color[0] = 0;
			color[1] = 0;
			color[2] = 1;
			color[3] = 1;
		}

		ShooterIndex = -1;
		ArrowTimer = 0;
		Life = 100;
		Lifetimer = 1000.0f;
	}
	else if (ObjectType == OBJECT_BUILDING)
	{

		size = 80;
		color[0] = 1;
		color[1] = 1;
		color[2] = 1;
		color[3] = 1;

		Life = 500;
		Lifetimer = 500.0f;

		BulletTimer = 0.0f;
		PlayerTimer = 0.0f;
	}
	else if (ObjectType == OBJECT_BULLET)
	{
		if (Team == 1)
		{
			vX = 600.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
			vY = abs(600.f *(((float)std::rand() / (float)RAND_MAX) - 1.5f)) * -1;

			color[0] = 1;
			color[1] = 0;
			color[2] = 0;
			color[3] = 1;
		}
		if (Team == 2)
			{
				vX = 600.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
				vY = abs(600.f *(((float)std::rand() / (float)RAND_MAX) - 1.5f));

				color[0] = 0;
				color[1] = 0;
				color[2] = 1;
				color[3] = 1;
		}

		size = 4;

		Life = 15;
		Lifetimer = 500.0f;

		BulletTimer = 0.0f;
	}
	else if (ObjectType == OBJECT_ARROW)
	{

		size = 4;

		if (Team == 1)
		{
			vX = 200.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
			vY =  abs(200.f *(((float)std::rand() / (float)RAND_MAX) - 1.5f)) * -1;

			color[0] = 0.5;
			color[1] = 0.2;
			color[2] = 0.7;
			color[3] = 1;
		}
		else if (Team == 2)
		{
			vX =  200.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
			vY = abs(200.f *(((float)std::rand() / (float)RAND_MAX) - 1.5f)) ;
			color[0] = 1;
			color[1] = 1;
			color[2] = 0;
			color[3] = 1;
		}

		Life = 15;
		Lifetimer = 500.0f;
	}
}

Object::~Object()
{
}

void Object::Update(float elapsedTime)
{
	float elapsedTimeInSecond = elapsedTime / 1000.f;
	
	if (ObjectType == OBJECT_BUILDING)
	{
		BulletTimer += elapsedTimeInSecond;
		PlayerTimer += elapsedTimeInSecond;
	}
	else if (ObjectType == OBJECT_CHARACTER)
		ArrowTimer += elapsedTimeInSecond;
	
	if (ObjectType != OBJECT_BUILDING)
	{
		Lifetimer -= 0.02f;
		//std::cout << Lifetimer << std::endl;
		posX = posX + vX * elapsedTimeInSecond;
		posY = posY + vY * elapsedTimeInSecond;

		if (posX > 250)
		{
			posX = 250;

			if (ObjectType == OBJECT_BULLET || ObjectType == OBJECT_ARROW)
			{
				Life = 0.f;
			}

			vX = -vX;
		}

		if (posX < -250)
		{
			posX = -250;

			if (ObjectType == OBJECT_BULLET || ObjectType == OBJECT_ARROW)
			{
				Life = 0.f;
			}

			vX = -vX;
		}

		if (posY > 400)
		{
			posY = 400;

			if (ObjectType == OBJECT_BULLET || ObjectType == OBJECT_ARROW)
			{
				Life = 0.f;
			}

			vY = -vY;
		}

		if (posY < -400)
		{
			posY = -400;

			if (ObjectType == OBJECT_BULLET || ObjectType == OBJECT_ARROW)
			{
				Life = 0.f;
			}

			vY = -vY;
		}
	}
}

float Object::GetTime()
{
	return Lifetimer;
}