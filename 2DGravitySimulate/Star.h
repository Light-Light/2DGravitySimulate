#pragma once

#include "Color.h"
#include "Display.h"
#include <vector>
#include <cmath>
#include <windows.h>

#define PI acos(-1)

using std::vector;

struct vec2d {
	float x;
	float y;
};

class Star {
private:
	static vector<Star*> createds;
	Color color;
	vec2d pos;
	float r;
	float mass;
	float rho = 300;
	DWORD lastMove = GetTickCount64();
	bool removeable = true;
	vec2d velocity;
	void flushRadius();
public:
	static void flushLastMove();
	Star(Color _color, vec2d _pos, float _mass, vec2d _velocity);
	~Star();
	Color getColor();
	vec2d getPosition();
	float getRadius();
	float getMass();
	float getRho();
	bool isRemoveable();
	vec2d getVelocity();
	void setColor(Color);
	void setPosition(vec2d);
	void setMass(float);
	void setRho(float);
	void setRemoveable(bool);
	void setVelocity(vec2d);
	static bool isCollided(Star*, Star*, float);
	void move();
	void display(Display,float);
};