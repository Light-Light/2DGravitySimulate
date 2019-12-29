#pragma once

enum class DefaultColor {
	RED,GREEN,BULE,WHITE,BLACK,YELLO,MAGENTA,CYAN,CUSTOM
};

class Color {
	DefaultColor color;
	float r = 0;
	float g = 0;
	float b = 0;
	float a = 0;
public:
	Color(DefaultColor, float);
	Color(float _r, float _g, float _b, float _a) :r(_r), g(_g), b(_b), a(_a), color(DefaultColor::CUSTOM) {};
	DefaultColor getColorType();
	float getRed();
	float getGreen();
	float getBlue();
	float getAlpha();
};