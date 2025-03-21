#pragma once
#include "raylib.h"

class ColorWheelGUI {
	private:
	    int width;
	    int height;
	    Vector2 position;
	    Texture2D colorWheelTexture;
		Texture2D squareTexture;
		Color* color;

	    void generateColorWheelTexture();
	public:
	    ColorWheelGUI(int width, int height, Vector2 position, Color* color);
	    ~ColorWheelGUI();

		void generateSquareTexture();
	    void render();
};
