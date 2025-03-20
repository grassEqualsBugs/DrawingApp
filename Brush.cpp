#include "include/Brush.hpp"

Brush::Brush() {
	Brush::size = 0;
	Brush::color = BLACK;
}

Brush::Brush(int size, Color color) {
	Brush::size = size;
	Brush::color = color;
}

void Brush::setSize(int size) {
	Brush::size = size;
}

void Brush::setColor(Color color) {
	Brush::color = color;
}

int Brush::getSize() {
	return size;
}

Color Brush::getColor() {
	return color;
}

void Brush::render(int x, int y) {
	DrawCircle(x, y, size, color);
}
