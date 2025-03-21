#pragma once
#include "raylib.h"
#include "ColorWheelGUI.hpp"

class ColorPickerGUI {
	private:
	    int size;
	    Vector2 position;
	    ColorWheelGUI colorWheel;
		Color selectedColor;
	public:
	    ColorPickerGUI(int size, Vector2 position, Color intialColor);
	    void render();
};
