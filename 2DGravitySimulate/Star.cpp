#include "Star.h"

vector<Star*> Star::createds = vector<Star*>();

Star::Star(Color _color, vec2d _pos, float _mass, vec2d _velocity) : color(_color), pos(_pos), mass(_mass), velocity(_velocity) {
	flushRadius();
	createds.push_back(this);
}

Star::~Star() {
	vector<Star*>::iterator it = find(createds.begin(), createds.end(), this);
	if (it != createds.end())
		createds.erase(it);
}

void Star::flushLastMove() {
	for (Star* star : createds)
		star->lastMove = GetTickCount64();
}

void Star::flushRadius() {
	r = sqrt(getMass() / getRho() / PI);
}

Color Star::getColor() {
	return color;
}

vec2d Star::getPosition() {
	return pos;
}

float Star::getRadius() {
	return r;
}

float Star::getMass() {
	return mass;
}

float Star::getRho() {
	return rho;
}

bool Star::isRemoveable() {
	return removeable;
}

vec2d Star::getVelocity() {
	return velocity;
}

void Star::setColor(Color _color) {
	color = _color;
}

void Star::setPosition(vec2d _pos) {
	pos = _pos;
}

void Star::setMass(float _mass) {
	mass = _mass;
	flushRadius();
}

void Star::setRho(float _rou) {
	rho = _rou;
	flushRadius();
}

void Star::setRemoveable(bool _removeable) {
	removeable = _removeable;
}

void Star::setVelocity(vec2d _velocity) {
	velocity = _velocity;
}

bool Star::isCollided(Star* star1, Star* star2, float distance) {
	return (star1->getRadius() + star2->getRadius()) <= distance;
}

void Star::move() {
	DWORD now = GetTickCount64();
	if (removeable) {
		float moveDown = ((float)(now - lastMove)) / 1000.0f;
		vec2d _pos = getPosition();
		vec2d _velocity = getVelocity();
		_pos.x += _velocity.x * moveDown;
		_pos.y += _velocity.y * moveDown;
		setPosition(_pos);
	}
	lastMove = now;
}

void Star::display(Display _display,float compressNum) {
	vec2d _pos = getPosition();
	_display.drawCircle({ _pos.x / compressNum,_pos.y / compressNum,0 }, r / compressNum, color);
}