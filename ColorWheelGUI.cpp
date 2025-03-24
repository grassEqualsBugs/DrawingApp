#include "include/ColorWheelGUI.hpp"

ColorWheelGUI::ColorWheelGUI(int width, int height, Vector2 position, Vector2 offset, Color color)
    : width(width), height(height), position(position), offset(offset), color(color)  {
    innerRadius = (float)6.5*width/20;
    outerRadius = (float)9*width/20;
    generateColorWheelTexture();
    hsvColor = ColorUtils::rgbToHSV(color);
    generateSquareTexture();
}

ColorWheelGUI::~ColorWheelGUI() {
    UnloadTexture(colorWheelTexture);
    UnloadTexture(squareTexture);
}

Rectangle ColorWheelGUI::getColorWheelRect() {
	return (Rectangle){-(float)width + position.x + offset.x, position.y + offset.y, (float)width, (float)height};
}

void ColorWheelGUI::generateColorWheelTexture() {
	Image img = GenImageColor(width, height, BLANK);
	Vector2 center = {(float)width/2, (float)height/2};
	int radius = (float)width/3;
	for (float theta = 0; theta < 2*PI; theta += 0.005) {
		for (int radius = innerRadius; radius < outerRadius; radius++) {
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

    Vector2 center = (Vector2){-(float)width / 2 + position.x + offset.x, (float)height/2 + position.y + offset.y};
    DrawCircleLinesV(center, innerRadius, BLACK);
    DrawCircleLinesV(center, outerRadius, BLACK);
    float wheelSelectorRadius = (outerRadius - innerRadius) / 2;
    float wheelSelectorPositionRadius = (outerRadius + innerRadius) / 2;
    float angle = PI/180*hsvColor[0];
    Vector2 wheelSelectorPosition = (Vector2){
    	cos(angle)*wheelSelectorPositionRadius + center.x,
    	-sin(angle)*wheelSelectorPositionRadius + center.y
    };
    for (int thicknessChange = 0; thicknessChange < 3; thicknessChange++) {
    	DrawCircleLinesV(wheelSelectorPosition, wheelSelectorRadius - thicknessChange, WHITE);
    }
}
