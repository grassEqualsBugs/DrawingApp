#include "include/Stroke.hpp"

Stroke::Stroke() { }

Stroke::Stroke(Vector2 position, Brush brush) {
	Stroke::brush = brush;
	positions.push_back(position);
}

void Stroke::update(Vector2 position) {
	positions.push_back(position);
}

void Stroke::render() {
	if (positions.size() == 0) return;
	for (int i = 0; i < positions.size()-1; i++) {
		brush.render(positions[i].x, positions[i].y);
		DrawLineEx(positions[i], positions[i+1],
			2*brush.getSize(), brush.getColor());
	}
	Vector2 finalPosition = positions[positions.size()-1];
	brush.render(finalPosition.x, finalPosition.y);
}
