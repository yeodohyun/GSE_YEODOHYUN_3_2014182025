#pragma once
#include <random>
class Object
{
private:
public:
	float x, y, z, r=255, g=255, b=255, size, a;
	float vx, vy, vz;
	int Xs = rand()%2, Ys = rand()%2;
	Object();
	Object(int x,int y);
	~Object();

	void Update();
	void SetVector(float vx, float vy, float vz);
};

