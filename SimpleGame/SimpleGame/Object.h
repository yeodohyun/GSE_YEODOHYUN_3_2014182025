#pragma once
class Object
{
private:
public:
	float x, y, z, r, g, b, size, a;
	int Xs = 0, Ys = 0;
	Object();
	Object(int x,int y);
	~Object();

	void Update();
};

