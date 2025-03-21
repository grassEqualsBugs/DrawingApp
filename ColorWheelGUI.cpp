#include "include/ColorWheelGUI.hpp"

ColorWheelGUI::ColorWheelGUI(int width, int height, Vector2 position)
    : width(width), height(height), position(position) {
    generateColorWheelTexture();
}

ColorWheelGUI::~ColorWheelGUI() {
    UnloadTexture(colorWheelTexture);
}

void ColorWheelGUI::generateColorWheelTexture() {
    Image img = GenImageColor(width, height, BLANK);

    colorWheelTexture = LoadTextureFromImage(img);
    UnloadImage(img);
}

void ColorWheelGUI::render() {
    DrawTexture(colorWheelTexture, position.x, position.y, WHITE);
    Vector2 center = {-(float)width/2 + position.x, (float)height/2 + position.y};
    float innerRadius = (float)width/3;
    float outerRadius = (float)9*width/20;

    DrawCircleLinesV(center, innerRadius, BLACK);
    DrawCircleLinesV(center, outerRadius, BLACK);
    DrawRectangleLines(center.x - (float)width/5, center.y - (float)height/5, 2*(float)width/5, 2*(float)height/5, BLACK);
}
