#pragma once
#include <vector>
#include "Stroke.hpp"

class Layer {
	private:
		std::vector<Stroke> strokes;
	public:
		Layer();
		void drawStroke(Stroke stroke);
		void removeLastStroke();
		void clearStrokes();
		void render();
};
