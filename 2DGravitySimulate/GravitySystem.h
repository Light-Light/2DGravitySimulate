#pragma once
#include <vector>
#include "Star.h"

using std::vector;

constexpr auto G = 0.01f;

class GravitySystem {
	float compressNum;
	bool canCollide = true;
public:
	vector<Star*> stars;
	GravitySystem(float _compressNum) :compressNum(_compressNum) {};
	void addStar(Star*);
	void removeStar(Star*);
	float getCompressNum();
	bool getCanCollide();
	void setCompressNum(float);
	void setCanCollide(bool);
	void moveAll();
	void checkCollision();
	void drawAll(Display);
};