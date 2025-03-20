#pragma once
#include "raylib.h"
#include "Brush.hpp"
#include <vector>

class Stroke {
	private:
		std::vector<Vector2> positions;
		Brush brush;
	public:
		Stroke();
		// on first intialization, we just add current mouse position to the array of positions
		Stroke(Vector2 position, Brush brush);
		void update(Vector2 position);
		void setBrush(Brush brush);
		Brush getBrush();
		void render();
};
