#include "stdafx.h"
#include "Object.h"
#include "Renderer.h"
#include <iostream>

Object::Object() : x(-500), y(-500), z(0), size(30), r(255), g(0), b(0), a(0)
{

}
Object::Object(int x1,int y1) : x(x1), y(y1), z(0), size(20), a(0)
{

}


Object::~Object()
{
}

void Object::SetVector(float x, float y, float z)
{
	vx = x;
	vy = y;
	vz = z;
}

void Object::Update()
{
	if (Xs == 0) 
	{
		x -= vx;
		if (x < -250)
			Xs = 1;
	}
	else if (Xs == 1) 
	{
		x += vx;
		if (x > 250)
			Xs = 0;
	}

	if (Ys == 0) 
	{
		y -= vy;
		if (y < -250)
			Ys = 1;
	}
	else if (Ys == 1) 
	{
		y += vy;
		if (y > 250)
			Ys = 0;
	}

}