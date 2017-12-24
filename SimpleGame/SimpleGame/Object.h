#pragma once

enum {
	OBJECT_CHARACTER = 1,
	OBJECT_CHARACTER2 = 2,
	OBJECT_CHARACTER3 = 3,
	OBJECT_CHARACTER4 = 4,
	OBJECT_BUILDING = 5,
	OBJECT_BULLET = 6,
	OBJECT_ARROW = 7,
	Steering = 10
};

class Object
{
public:

	float posX, posY;
	float vX, vY;
	int size, color[4];

	float Life;
	float Lifetimer;

	int ObjectType;

	float BulletTimer;
	float PlayerTimer;
	float PlayerTimer2[4][4];

	float ArrowTimer;
	int ShooterIndex;

	int Team;
	float ParticleTimer;

	bool CharacterReady;
	int slow;
	int damage;

	Object();
	Object(float x, float y, int Type);
	Object(float x, float y, int Type, int team);
	~Object();
	void Update(float elapsedTime);
	float GetTime();
};

