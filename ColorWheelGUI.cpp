#include "include/ColorWheelGUI.hpp"

ColorWheelGUI::ColorWheelGUI(int width, int height, Vector2 position, Vector2 offset, Color color)
    : width(width), height(height), position(position), offset(offset), color(color)  {
    generateColorWheelTexture();
    hsvColor = ColorUtils::rgbToHSV(color);
    generateSquareTexture();
}

ColorWheelGUI::~ColorWheelGUI() {
    UnloadTexture(colorWheelTexture);
    UnloadTexture(squareTexture);
}

void ColorWheelGUI::generateColorWheelTexture() {
	Image img = GenImageColor(width, height, BLANK);
	Vector2 center = {(float)width/2, (float)height/2};
	int radius = (float)width/3;
	for (float theta = 0; theta < 2*PI; theta += 0.001) {
		for (int radius = (float)width/3; radius < (float)9*width/20; radius++) {
			int x = center.x + cos(theta)*radius;
     		int y = center.y - sin(theta)*radius;
			ImageDrawPixel(&img, x, y, ColorUtils::hsvToRGB(theta*180/PI, 1, 1));
		}
	}
	colorWheelTexture = LoadTextureFromImage(img);
	UnloadImage(img);
}

void ColorWheelGUI::generateSquareTexture() {
	Image img = GenImageColor(width, height, BLANK);
	Vector2 center = {(float)width/2, (float)height/2};
	for (int x = center.x - (float)width/5; x <= center.x + (float)width/5; x++) {
		for (int y = center.y - (float)height/5; y <= center.y + (float)height/5; y++) {
			float normX = (x - (center.x - (float)width/5)) / ((2.0f * width) / 5);
			float normY = (y - (center.y - (float)height/5)) / ((2.0f * height) / 5);
			ImageDrawPixel(&img, x, y, ColorUtils::hsvToRGB(hsvColor[0], normX, 1-normY));
		}
	}
	squareTexture = LoadTextureFromImage(img);
	UnloadImage(img);
}

Color ColorWheelGUI::getSelectedColor() {
	return color;
}

void ColorWheelGUI::update() { }

void ColorWheelGUI::render() {
	DrawTexture(squareTexture, -(float)width + position.x + offset.x, position.y + offset.y, WHITE);
    DrawTexture(colorWheelTexture, -(float)width + position.x + offset.x, position.y + offset.y, WHITE);
}
