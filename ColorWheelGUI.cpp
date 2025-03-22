#include "include/ColorWheelGUI.hpp"

ColorWheelGUI::ColorWheelGUI(int width, int height, Vector2 position, Color color)
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
        static_cast<unsigned char>(255)
    };
}

std::vector<float> rgbToHSV(Color color) {
    float r = (int)color.r / 255.0f;
    float g = (int)color.g / 255.0f;
    float b = (int)color.b / 255.0f;
    float maxVal = std::max({r, g, b});
    float minVal = std::min({r, g, b});
    float delta = maxVal - minVal;

    float h = 0.0f, s = 0.0f, v = maxVal;

    if (delta > 0.0f) {
        if (maxVal == r) {
            h = 60.0f * fmod(((g - b) / delta), 6);
        } else if (maxVal == g) {
            h = 60.0f * (((b - r) / delta) + 2);
        } else if (maxVal == b) {
            h = 60.0f * (((r - g) / delta) + 4);
        }

        if (maxVal > 0.0f) {
            s = delta / maxVal;
        }
    }

    if (h < 0.0f) {
        h += 360.0f;
    }

    return {h, s, v};
}

void ColorWheelGUI::generateColorWheelTexture() {
	Image img = GenImageColor(width, height, BLANK);
	Vector2 center = {(float)width/2, (float)height/2};
	int radius = (float)width/3;
	for (float theta = 0; theta < 2*PI; theta += 0.001) {
		for (int radius = (float)width/3; radius < (float)9*width/20; radius++) {
			int x = center.x + cos(theta)*radius;
     		int y = center.y - sin(theta)*radius;
			ImageDrawPixel(&img, x, y, hsvToRGB(theta*180/PI, 1, 1));
		}
	}
	colorWheelTexture = LoadTextureFromImage(img);
	UnloadImage(img);
}

void ColorWheelGUI::generateSquareTexture() {
	Image img = GenImageColor(width, height, BLANK);
	std::vector<float> hsv = rgbToHSV(color);
	Vector2 center = {(float)width/2, (float)height/2};
	for (int x = center.x - (float)width/5; x <= center.x + (float)width/5; x++) {
		for (int y = center.y - (float)height/5; y <= center.y + (float)height/5; y++) {
			float normX = (x - (center.x - (float)width/5)) / ((2.0f * width) / 5);
			float normY = (y - (center.y - (float)height/5)) / ((2.0f * height) / 5);
			ImageDrawPixel(&img, x, y, hsvToRGB(hsv[0], normX, 1-normY));
		}
	}
	squareTexture = LoadTextureFromImage(img);
	UnloadImage(img);
}

void ColorWheelGUI::render() {
	DrawTexture(squareTexture, -(float)width + position.x, position.y, WHITE);
    DrawTexture(colorWheelTexture, -(float)width + position.x, position.y, WHITE);
}
