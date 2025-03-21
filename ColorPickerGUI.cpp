#include "include/ColorPickerGUI.hpp"

ColorPickerGUI::ColorPickerGUI(int size, Vector2 position, Color initialColor)
    : size(size), position(position), selectedColor(initialColor), colorWheel(size*6, size*6, position) {}

void ColorPickerGUI::render() {
    DrawRectangle(position.x, position.y, size, size, selectedColor);
    colorWheel.render();
}
