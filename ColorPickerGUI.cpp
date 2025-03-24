#include "include/ColorPickerGUI.hpp"

ColorPickerGUI::ColorPickerGUI(int size, Vector2 position, Color initialColor)
    : size(size), position(position), selectedColor(initialColor), wheelOpen(false),
    colorWheel(size*4, size*4, position, (Vector2){-30.f, 30.f}, initialColor) {}

bool ColorPickerGUI::isWheelOpen() {
	return wheelOpen;
}

Color ColorPickerGUI::getSelectedColor() {
	return selectedColor;
}

void ColorPickerGUI::update() {
	Rectangle rect = (Rectangle){position.x, position.y, (float)size, (float)size};
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		if (CheckCollisionPointRec(GetMousePosition(), rect)) {
			wheelOpen = !wheelOpen;
		} else if (!CheckCollisionPointRec(GetMousePosition(), colorWheel.getColorWheelRect())) {
			wheelOpen = false;
		}
	}
}

void ColorPickerGUI::render() {
	Rectangle rect = (Rectangle){position.x, position.y, (float)size, (float)size};
	Color guiColor = (Color){125, 125, 125, 255};
	DrawCircle(position.x + (float)size / 2, position.y + (float)size / 2, size, guiColor);
    DrawRectangleRounded(rect, 0.5, 20, selectedColor);
    if (wheelOpen) {
    	DrawRectangleRounded(colorWheel.getColorWheelRect(), 0.5, 20, guiColor);
    	colorWheel.render();
    }
}
