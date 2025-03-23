#include "include/ColorPickerGUI.hpp"

ColorPickerGUI::ColorPickerGUI(int size, Vector2 position, Color initialColor)
    : size(size), position(position), selectedColor(initialColor), wheelOpen(false),
    colorWheel(size*4, size*4, position, (Vector2){-30.f, 30.f}, initialColor) {}

void ColorPickerGUI::update() {
	Rectangle rect = (Rectangle){position.x, position.y, (float)size, (float)size};
	if (CheckCollisionPointRec(GetMousePosition(), rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		wheelOpen = !wheelOpen;
	}
}

void ColorPickerGUI::render() {
	Rectangle rect = (Rectangle){position.x, position.y, (float)size, (float)size};
	DrawCircle(position.x + (float)size / 2, position.y + (float)size / 2, size, DARKGRAY);
    DrawRectangleRounded(rect, 0.2, 20, selectedColor);
    if (wheelOpen) colorWheel.render();
}
