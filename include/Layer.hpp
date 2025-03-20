#pragma once
#include <vector>
#include "Stroke.hpp"

class Layer {
	private:
		std::vector<Stroke> strokes;
		RenderTexture renderTexture;
	public:
		Layer(int width, int height);
		void drawStroke(Stroke stroke);
		void removeLastStroke();
		void clearStrokes();
		void updateRenderTexture();
		void render();
};
