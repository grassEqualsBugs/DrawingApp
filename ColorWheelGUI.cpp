#include "include/ColorWheelGUI.hpp"
#include "include/raylib.h"

ColorWheelGUI::ColorWheelGUI(int width, int height, Vector2 position, Vector2 offset, Color color)
    : width(width), height(height), position(position), offset(offset), color(color)  {
    innerRadius = (float)6.5*width/20;
    outerRadius = (float)9*width/20;
    generateColorWheelTexture();
    hsvColor = ColorUtils::rgbToHSV(color);
    squareScaleFactor = 5.3;
    generateSquareTexture();
    isWheelUpdating = false;
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
	for (int x = center.x - (float)width/squareScaleFactor; x <= center.x + (float)width/squareScaleFactor; x++) {
		for (int y = center.y - (float)height/squareScaleFactor; y <= center.y + (float)height/squareScaleFactor; y++) {
			float normX = (x - (center.x - (float)width/squareScaleFactor)) / ((2.0f * width) / squareScaleFactor);
			float normY = (y - (center.y - (float)height/squareScaleFactor)) / ((2.0f * height) / squareScaleFactor);
			ImageDrawPixel(&img, x, y, ColorUtils::hsvToRGB({hsvColor[0], normX, 1-normY}));
		}
	}
	squareTexture = LoadTextureFromImage(img);
	UnloadImage(img);
}

Color ColorWheelGUI::getSelectedColor() {
	return color;
}

float clamp(float x, float l, float r) {
	if (l < x && x < r) return x;
	if (x > r) return r;
	if (x < l) return l;
	return x;
}

void ColorWheelGUI::update() {
	Vector2 mousePos = GetMousePosition();
	Vector2 center = (Vector2){-(float)width / 2 + position.x + offset.x, (float)height/2 + position.y + offset.y};
	float distance = sqrt((center.x - mousePos.x)*(center.x - mousePos.x) + (center.y - mousePos.y)*(center.y - mousePos.y));

	// outside color wheel
	if (distance <= outerRadius && innerRadius <= distance && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		isWheelUpdating = true;
	} else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
		isWheelUpdating = false;
	}
	if (isWheelUpdating) {
		double angle = -atan2(mousePos.y - center.y, mousePos.x - center.x);
		if (angle < 0) angle += 2*PI;
		hsvColor[0] = angle * 180 / PI;
		color = ColorUtils::hsvToRGB(hsvColor);
		generateSquareTexture();
	}

	// inside color square
	float xLeftBound = center.x - (float)width/squareScaleFactor;
	float xRightBound = center.x + (float)width/squareScaleFactor;
	float yLeftBound = center.y - (float)height/squareScaleFactor;
	float yRightBound = center.y + (float)height/squareScaleFactor;
	if (mousePos.x <= xRightBound && mousePos.x >= xLeftBound && mousePos.y <= yRightBound && mousePos.y >= yLeftBound && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		isSquareUpdating = true;
	} else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
		isSquareUpdating = false;
	}
	if (isSquareUpdating) {
		float normX = ((clamp(mousePos.x, xLeftBound, xRightBound) - xLeftBound)/(xRightBound - xLeftBound));
		float normY = ((clamp(mousePos.y, yLeftBound, yRightBound) - yLeftBound)/(yRightBound - yLeftBound));
		hsvColor[1] = normX;
		hsvColor[2] = 1 - normY;
		color = ColorUtils::hsvToRGB(hsvColor);
	}
}

void ColorWheelGUI::render() {
	DrawTexture(squareTexture, -(float)width + position.x + offset.x, position.y + offset.y, WHITE);
    DrawTexture(colorWheelTexture, -(float)width + position.x + offset.x, position.y + offset.y, WHITE);

    Vector2 center = (Vector2){-(float)width / 2 + position.x + offset.x, (float)height/2 + position.y + offset.y};

    // Color wheel
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

    // Color square
    Vector2 svSelectorPosition = (Vector2){
    	((hsvColor[1] * ((2.0f * width) / squareScaleFactor)) + (center.x - (float)width / squareScaleFactor)),
    	(((1 - hsvColor[2]) * ((2.0f * height) / squareScaleFactor)) + (center.y - (float)height / squareScaleFactor))
    };
    float svSelectorRadius = 5;
    for (float thicknessChange = 0; thicknessChange < 2; thicknessChange += 0.5) {
    	DrawCircleLinesV(svSelectorPosition, svSelectorRadius - thicknessChange, BLACK);
    }
}
