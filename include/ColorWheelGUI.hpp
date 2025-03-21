#pragma once
#include "raylib.h"

class ColorWheelGUI {
	private:
	    int width;
	    int height;
	    Vector2 position;
	    Texture2D colorWheelTexture;

	    void generateColorWheelTexture();
	public:
	    ColorWheelGUI(int width, int height, Vector2 position);
	    ~ColorWheelGUI();

	    void render();
};
