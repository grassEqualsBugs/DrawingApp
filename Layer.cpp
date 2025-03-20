#include "include/Layer.hpp"

Layer::Layer() { }

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

void Layer::render() {
	for (Stroke stroke : strokes) {
		stroke.render();
	}
}
