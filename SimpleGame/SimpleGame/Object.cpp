
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
	slow = 1;
	ParticleTimer = -0.5f;
	PlayerTimer = 0;
	CharacterReady = false;
	// 조종장치
	if (ObjectType == Steering)
	{
		vX = 0;
		vY = 0;

		size = 0;
		color[0] = 0;
		color[1] = 0;
		color[2] = 0;
		color[3] = 0;
		ShooterIndex = -1;
		ArrowTimer = 0;
		Life = 100;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				PlayerTimer2[i][j] = 0.0f;
		}
	}

	if (ObjectType == OBJECT_CHARACTER)
	{
		vX = 200.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		vY = 0;

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
		Life = 20;
		damage = 30;
	}
	else if(ObjectType == OBJECT_CHARACTER2)
	{

		size = 50;

		if (Team == 1)
		{
			vX = 0;
			vY = -80.0f;

			color[0] = 1;
			color[1] = 0;
			color[2] = 0;
			color[3] = 1;
		}
		else if (Team == 2)
		{
			vX = 0;
			vY = 80.f;

			color[0] = 0;
			color[1] = 0;
			color[2] = 1;
			color[3] = 1;
		}

		ShooterIndex = -1;
		ArrowTimer = 0;
		Life = 200;
		damage = 100;
	}
	else if (ObjectType == OBJECT_CHARACTER3)
	{
		vX = 0;
		vY = 0;

		size = 80;

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
		Life = 50;
		damage = 1000;
	}
	else if (ObjectType == OBJECT_CHARACTER4)
	{
		vX = 200.f *(((float)std::rand() / (float)RAND_MAX) - 1.5f);
		vY = 200.f *(((float)std::rand() / (float)RAND_MAX) - 1.5f);

		size = 150;

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
		Life = 50;
		damage = 100;
	}
	else if (ObjectType == OBJECT_BUILDING)
	{

		size = 80;
		color[0] = 1;
		color[1] = 1;
		color[2] = 1;
		color[3] = 1;

		Life = 500;

		BulletTimer = 0.0f;

	}
	else if (ObjectType == OBJECT_BULLET)
	{
		if (Team == 1)
		{
			vX = 200.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
			vY = abs(200.f *(((float)std::rand() / (float)RAND_MAX) - 1.5f)) * -1;

			color[0] = 1;
			color[1] = 0;
			color[2] = 0;
			color[3] = 1;
		}
		if (Team == 2)
		{
			vX = 200.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
			vY = abs(200.f *(((float)std::rand() / (float)RAND_MAX) - 1.5f));

			color[0] = 0;
			color[1] = 0;
			color[2] = 1;
			color[3] = 1;
		}

		size = 4;

		Life = 10;
		damage = 15;

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

		Life = 10;
		damage = 10;
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
	}
	else if (ObjectType == OBJECT_CHARACTER)
		ArrowTimer += elapsedTimeInSecond;

	if (ObjectType == OBJECT_CHARACTER4)
		Life -= elapsedTime / 100;


	if (ObjectType == Steering) {
		ParticleTimer += 0.002f;
		if (ParticleTimer > 50.0f)
			ParticleTimer = 0;
	}
	if (ObjectType != OBJECT_BUILDING && ObjectType != Steering)
	{
		//std::cout << Lifetimer << std::endl;
		posX = posX + vX * elapsedTimeInSecond / slow;
		posY = posY + vY * elapsedTimeInSecond / slow;
		if (ObjectType == OBJECT_BULLET)
		{
			ParticleTimer += 0.002f;
			if (ParticleTimer > 50.0f)
				ParticleTimer = 0;
		}
		if (posX > 150)
		{
			posX = 150;

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

		if (posY > 350)
		{
			posY = 350;

			if (ObjectType == OBJECT_BULLET || ObjectType == OBJECT_ARROW)
			{
				Life = 0.f;
			}

			vY = -vY;
		}

		if (posY < -350)
		{
			posY = -350;

			if (ObjectType == OBJECT_BULLET || ObjectType == OBJECT_ARROW)
			{
				Life = 0.f;
			}

			vY = -vY;
		}
		if (!(ObjectType == OBJECT_ARROW) && !(ObjectType == OBJECT_BULLET) &&!(OBJECT_CHARACTER4))
		{
			if (slow == 1)
			{
				if (posY<150 && posY>-150)
				{
					slow = 2;
				}
			}
			else if (slow == 2)
			{
				if (posY > 150 || posY < -150)
				{
					slow = 1;
				}
			}
		}
	}
}
