#include "include/ColorWheelGUI.hpp"
#include <cmath>
#include <algorithm>

ColorWheelGUI::ColorWheelGUI(int width, int height, Vector2 position, Color* color)
    : width(width), height(height), position(position), color(color)  {
    generateColorWheelTexture();
    generateSquareTexture();
}

ColorWheelGUI::~ColorWheelGUI() {
    UnloadTexture(colorWheelTexture);
    UnloadTexture(squareTexture);
}

Color hsvToRGB(float h, float s, float v) {
    float r = 0, g = 0, b = 0;
    int hi = static_cast<int>(h / 60) % 6;
    float f = (h / 60.0f) - hi;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1 - (1 - f) * s);

    switch (hi) {
        case 0: r = v, g = t, b = p; break;
        case 1: r = q, g = v, b = p; break;
        case 2: r = p, g = v, b = t; break;
        case 3: r = p, g = q, b = v; break;
        case 4: r = t, g = p, b = v; break;
        case 5: r = v, g = p, b = q; break;
    }

    return (Color){
        static_cast<unsigned char>(r * 255),
        static_cast<unsigned char>(g * 255),
        static_cast<unsigned char>(b * 255),
        255
    };
}

// Convert RGB (0-255) to HSV (0-360, 0-1, 0-1)
void rgbToHSV(unsigned char r, unsigned char g, unsigned char b, float &h, float &s, float &v) {
    float rf = (float)static_cast<int>(r) / 255.0f;
    float gf = (float)static_cast<int>(g) / 255.0f;
    float bf = (float)static_cast<int>(b) / 255.0f;

    float maxVal = std::max({rf, gf, bf});
    float minVal = std::min({rf, gf, bf});
    float delta = maxVal - minVal;

    // Compute Hue
    if (delta == 0) {
        h = 0;
    } else if (maxVal == rf) {
        h = 60 * (fmod(((gf - bf) / delta), 6));
    } else if (maxVal == gf) {
        h = 60 * (((bf - rf) / delta) + 2);
    } else {
        h = 60 * (((rf - gf) / delta) + 4);
    }
    if (h < 0) h += 360;

    // Compute Saturation
    s = (maxVal == 0) ? 0 : (delta / maxVal);

    // Compute Value
    v = maxVal;
}

void ColorWheelGUI::generateColorWheelTexture() {
	Image img = GenImageColor(width, height, BLANK);
	Vector2 center = {(float)width/2, (float)height/2};
	int radius = (float)width/3;
	for (float theta = 0; theta < 2*PI; theta += 0.001) {
		for (int radius = (float)width/3; radius < (float)9*width/20; radius++) {
			int x = center.x + cos(theta)*(radius);
     		int y = center.y - sin(theta)*(radius);
			ImageDrawPixel(&img, x, y, hsvToRGB(theta*180/PI, 1, 1));
		}
	}
	colorWheelTexture = LoadTextureFromImage(img);
	UnloadImage(img);
}

void ColorWheelGUI::generateSquareTexture() {
	Image img = GenImageColor(width, height, BLANK);
	float currH = 0; float currS = 0; float currV = 0;
 	rgbToHSV(color->r, color->g, color->b, currH, currS, currV);
	Vector2 center = {(float)width/2, (float)height/2};
	for (int x = center.x - (float)width/5; x <= center.x + (float)width/5; x++) {
		for (int y = center.y - (float)height/5; y <= center.y + (float)height/5; y++) {
			float normX = (x - (center.x - (float)width/5)) / ((2.0f * width) / 5);
			float normY = (y - (center.y - (float)height/5)) / ((2.0f * height) / 5);
			ImageDrawPixel(&img, x, y, hsvToRGB(currH, normX, 1-normY));
		}
	}
	squareTexture = LoadTextureFromImage(img);
	UnloadImage(img);
}

void ColorWheelGUI::render() {
	DrawTexture(squareTexture, -(float)width + position.x, position.y, WHITE);
    DrawTexture(colorWheelTexture, -(float)width + position.x, position.y, WHITE);
}
