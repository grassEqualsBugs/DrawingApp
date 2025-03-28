#pragma once
#include "raylib.h"
#include "ColorWheelGUI.hpp"

class ColorPickerGUI {
	private:
	    int size;
	    Vector2 position;
	    ColorWheelGUI colorWheel;
		bool wheelOpen;
		Color selectedColor;
	public:
	    ColorPickerGUI(int size, Vector2 position, Color intialColor);
		bool isWheelOpen();
		Color getSelectedColor();
		void update();
	    void render();
};
