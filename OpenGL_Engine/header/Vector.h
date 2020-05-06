#pragma once


class Vector
{
public:
	Vector(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	~Vector()
	{
	}

public:
	float x, y, z;
};

class Vector4 :public Vector
{
public:
	Vector4(float x, float y, float z,float w) :Vector(x,y,z){
		this->w = w;
	}

public:
	float w;

};

