#pragma once
#include <vector>
#include "Stroke.hpp"
#include <iostream>
#include "ColorUtils.hpp"

class Layer {
	private:
		std::vector<Stroke> strokes;
		RenderTexture renderTexture;
	public:
		Layer(int width, int height);
		void drawStroke(Stroke stroke);
		void removeLastStroke();
		void restart();
		void fill(Vector2 position, Color fillColor);
		void render();
};
