#pragma once
#include "raylib.h"
#include "ColorUtils.hpp"
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>

class ColorWheelGUI {
	private:
	    int width;
	    int height;
	    Vector2 position;
	    Texture2D colorWheelTexture;
		Texture2D squareTexture;
		Color color;
		std::vector<float> hsvColor;
		Vector2 offset;

	    void generateColorWheelTexture();
		void generateSquareTexture();
	public:
	    ColorWheelGUI(int width, int height, Vector2 position, Vector2 offset, Color color);
	    ~ColorWheelGUI();

		Color getSelectedColor();
		void update();
	    void render();
};
