#pragma once
#include <random>
class Object
{
private:
public:
	float x, y, z, r, g, b, size, a;
	int Xs = rand()%2, Ys = rand()%2;
	Object();
	Object(int x,int y);
	~Object();

	void Update();
};

