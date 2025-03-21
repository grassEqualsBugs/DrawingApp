#include "include/Layer.hpp"

Layer::Layer(int width, int height) {
	renderTexture = LoadRenderTexture(width, height);
}

void Layer::drawStroke(Stroke stroke) {
	strokes.push_back(stroke);
}

void Layer::removeLastStroke() {
	if (strokes.size() == 0) return;
	strokes.pop_back();
}

void Layer::clearStrokes() {
	strokes.clear();
	strokes.shrink_to_fit();
}

void Layer::updateRenderTexture() {
	BeginTextureMode(renderTexture);
	ClearBackground(WHITE);
	for (Stroke stroke : strokes) {
		stroke.render();
	}
	EndTextureMode();
}

void Layer::render() {
	DrawTextureRec(
	    renderTexture.texture,
	    (Rectangle){0, 0, (float)renderTexture.texture.width, -(float)renderTexture.texture.height},
	    (Vector2){0, 0},
	    WHITE
	);
}
