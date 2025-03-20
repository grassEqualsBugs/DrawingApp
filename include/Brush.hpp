#pragma once
#include "raylib.h"

class Brush {
	private:
		int size;
		Color color;
	public:
		Brush();
		Brush(int size, Color color);
		void setColor(Color color);
		void setSize(int size);
		Color getColor();
		int getSize();
		void render(int x, int y);
};
