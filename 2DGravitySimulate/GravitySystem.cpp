#include "GravitySystem.h"
#include <map>

using std::vector;

void GravitySystem::addStar(Star* star) {
	stars.push_back(star);
}

void GravitySystem::removeStar(Star* star) {
	vector<Star*>::iterator it = find(stars.begin(), stars.end(), star);
	if (it != stars.end())
		stars.erase(it);
}

float GravitySystem::getCompressNum() {
	return compressNum;
}

bool GravitySystem::getCanCollide(){
	return canCollide;
}

void GravitySystem::setCanCollide(bool _canCollide) {
	canCollide = _canCollide;
}

void GravitySystem::setCompressNum(float _compressNum) {
	compressNum = _compressNum;
}

namespace TEMP {
	vec2d vecChange = { 0,0 };
}

float gravity(float G, Star* star1, Star* star2, float distance) {
	if(distance >= star1->getRadius() + star2->getRadius())
		return G * star1->getMass() * star2->getMass() / (distance * distance);
	return 0;
}

void GravitySystem::moveAll() {

	for (Star* star : stars) {
		vec2d starPos = star->getPosition();
		for (Star* acting : stars) {
			if (star != acting) {

				vec2d actingPos = acting->getPosition();
				float distance = sqrt(pow(starPos.x - actingPos.x,2) + pow(starPos.y - actingPos.y,2));

				float force = gravity(G,star,acting,distance);
				float acceledSpeed = force / star->getMass();

				if (starPos.x == actingPos.x) {
					if (starPos.y < actingPos.y) {
						TEMP::vecChange.y = acceledSpeed;
					}else {
						TEMP::vecChange.y = -acceledSpeed;
					}
				}else if (starPos.y == actingPos.y) {
					if (starPos.x < actingPos.x) {
						TEMP::vecChange.x = acceledSpeed;
					}else {
						TEMP::vecChange.x = -acceledSpeed;
					}
				}else {
					float lengthRatio = distance / (distance - acceledSpeed);
					if (starPos.x < actingPos.x && starPos.y < actingPos.y) {

						float xDiff = actingPos.x - starPos.x;
						float yDiff = actingPos.y - starPos.y;
						float len = sqrt(xDiff * xDiff + yDiff * yDiff);
						float sinv = yDiff / len;
						float cosv = xDiff / len;
						TEMP::vecChange.y = acceledSpeed * sinv;
						TEMP::vecChange.x = acceledSpeed * cosv;

					}else if (starPos.x > actingPos.x && starPos.y > actingPos.y) {

						float xDiff = starPos.x - actingPos.x;
						float yDiff = starPos.y - actingPos.y;
						float len = sqrt(xDiff * xDiff + yDiff * yDiff);
						float sinv = yDiff / len;
						float cosv = xDiff / len;
						TEMP::vecChange.y = -acceledSpeed * sinv;
						TEMP::vecChange.x = -acceledSpeed * cosv;

					}else if (starPos.x < actingPos.x && starPos.y > actingPos.y) {

						float xDiff = actingPos.x - starPos.x;
						float yDiff = starPos.y - actingPos.y;
						float len = sqrt(xDiff * xDiff + yDiff * yDiff);
						float sinv = yDiff / len;
						float cosv = xDiff / len;
						TEMP::vecChange.y = -acceledSpeed * sinv;
						TEMP::vecChange.x = acceledSpeed * cosv;

					}else if (starPos.x > actingPos.x && starPos.y < actingPos.y) {

						float xDiff = starPos.x - actingPos.x;
						float yDiff = actingPos.y - starPos.y;
						float len = sqrt(xDiff * xDiff + yDiff * yDiff);
						float sinv = yDiff / len;
						float cosv = xDiff / len;
						TEMP::vecChange.y = acceledSpeed * sinv;
						TEMP::vecChange.x = -acceledSpeed * cosv;

					}
				}

				vec2d oldVec = star->getVelocity();
				oldVec.x += TEMP::vecChange.x;
				oldVec.y += TEMP::vecChange.y;
				star->setVelocity(oldVec);

			}
		}
		star->move();
	}

}

void GravitySystem::checkCollision() {

	if (!canCollide)
		return;

	vec2d starPos;
	for (int i = 0; i < stars.size(); i++) {
		Star* star = stars[i];
		starPos = star->getPosition();
		for (int j = i + 1; j < stars.size(); j++) {
			Star* acting = stars[j];

			vec2d actingPos = acting->getPosition();
			float distance = sqrt(pow(starPos.x - actingPos.x, 2) + pow(starPos.y - actingPos.y, 2));

			if (!Star::isCollided(star, acting, distance)) {

				vec2d starSpeed = star->getVelocity();
				vec2d actingSpeed = acting->getVelocity();

				if (star->getMass() <= acting->getMass()) {

					removeStar(star);
					starSpeed.x *= star->getMass();
					starSpeed.y *= star->getMass();
					actingSpeed.x *= acting->getMass();
					actingSpeed.y *= acting->getMass();
					actingSpeed.x += starSpeed.x;
					actingSpeed.y += starSpeed.y;
					actingSpeed.x /= (star->getMass() + acting->getMass());
					actingSpeed.y /= (star->getMass() + acting->getMass());
					acting->setVelocity(actingSpeed);

					acting->setMass(acting->getMass() + star->getMass());

					goto a;

				}
				else if (star->getMass() > acting->getMass()) {

					removeStar(acting);
					starSpeed.x *= star->getMass();
					starSpeed.y *= star->getMass();
					actingSpeed.x *= acting->getMass();
					actingSpeed.y *= acting->getMass();
					starSpeed.x += actingSpeed.x;
					starSpeed.y += actingSpeed.y;
					starSpeed.x /= (star->getMass() + acting->getMass());
					starSpeed.y /= (star->getMass() + acting->getMass());
					star->setVelocity(starSpeed);

					star->setMass(star->getMass() + acting->getMass());

				}


			}
		}
	a: {};
	}

}

void GravitySystem::drawAll(Display display) {
	for (Star* star : stars) {
		star->display(display,compressNum);
	}
}