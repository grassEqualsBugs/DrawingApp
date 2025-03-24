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
			ImageDrawPixel(&img, x, y, ColorUtils::hsvToRGB({theta*180/PI, 1, 1}));
		}
	}
	colorWheelTexture = LoadTextureFromImage(img);
	UnloadImage(img);
}

void ColorWheelGUI::generateSquareTexture() {
	Image img = GenImageColor(width, height, BLANK);
	Vector2 center = {(float)width/2, (float)height/2};
	float k = 5.3;
	for (int x = center.x - (float)width/k; x <= center.x + (float)width/k; x++) {
		for (int y = center.y - (float)height/k; y <= center.y + (float)height/k; y++) {
			float normX = (x - (center.x - (float)width/k)) / ((2.0f * width) / k);
			float normY = (y - (center.y - (float)height/k)) / ((2.0f * height) / k);
			ImageDrawPixel(&img, x, y, ColorUtils::hsvToRGB({hsvColor[0], normX, 1-normY}));
		}
	}
	squareTexture = LoadTextureFromImage(img);
	UnloadImage(img);
}

Color ColorWheelGUI::getSelectedColor() {
	return color;
}

void ColorWheelGUI::update() {
	Vector2 mousePos = GetMousePosition();
	Vector2 center = (Vector2){-(float)width / 2 + position.x + offset.x, (float)height/2 + position.y + offset.y};
	float distance = sqrt((center.x - mousePos.x)*(center.x - mousePos.x) + (center.y - mousePos.y)*(center.y - mousePos.y));
	double angle = -atan2(mousePos.y - center.y, mousePos.x - center.x);
	if (angle < 0) angle += 2*PI;
	if (distance <= outerRadius && innerRadius <= distance && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		hsvColor[0] = angle * 180 / PI;
		color = ColorUtils::hsvToRGB(hsvColor);
		generateSquareTexture();
	}
}

void ColorWheelGUI::render() {
	DrawTexture(squareTexture, -(float)width + position.x + offset.x, position.y + offset.y, WHITE);
    DrawTexture(colorWheelTexture, -(float)width + position.x + offset.x, position.y + offset.y, WHITE);

    Vector2 center = (Vector2){-(float)width / 2 + position.x + offset.x, (float)height/2 + position.y + offset.y};
    DrawCircleLinesV(center, innerRadius - 1, BLACK);
    DrawCircleLinesV(center, outerRadius, BLACK);
    float wheelSelectorRadius = (outerRadius - innerRadius) / 2;
    float wheelSelectorPositionRadius = (outerRadius + innerRadius) / 2;
    float angle = PI/180*hsvColor[0];
    Vector2 wheelSelectorPosition = (Vector2){
    	cos(angle)*wheelSelectorPositionRadius + center.x,
    	-sin(angle)*wheelSelectorPositionRadius + center.y
    };
    for (float thicknessChange = 0; thicknessChange < 3; thicknessChange += 0.5) {
    	DrawCircleLinesV(wheelSelectorPosition, wheelSelectorRadius - thicknessChange, WHITE);
    }
}
