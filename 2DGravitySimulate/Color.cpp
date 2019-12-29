#include "Color.h"

Color::Color(DefaultColor _color, float _a):color(_color),a(_a) {
	if (_color == DefaultColor::RED) {
		r = 1;
	}else if (_color == DefaultColor::GREEN) {
		g = 1;
	}else if (_color == DefaultColor::BULE) {
		b = 1;
	}else if (_color == DefaultColor::WHITE) {
		r = 1;
		g = 1;
		b = 1;
	}else if (_color == DefaultColor::YELLO) {
		r = 1;
		g = 1;
	}else if (_color == DefaultColor::MAGENTA) {
		r = 1;
		b = 1;
	}else if (_color == DefaultColor::CYAN) {
		g = 1;
		b = 1;
	}
}

DefaultColor Color::getColorType() {
	return color;
}

float Color::getRed() {
	return r;
}

float Color::getGreen() {
	return g;
}

float Color::getBlue() {
	return b;
}

float Color::getAlpha() {
	return a;
}