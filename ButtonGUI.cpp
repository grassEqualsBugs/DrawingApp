#include "include/ButtonGUI.hpp"
#include "include/raylib.h"

ButtonGUI::ButtonGUI(int buttonSize, int iconSize, int buttonMargin) {
	ButtonGUI::buttonSize = buttonSize;
	ButtonGUI::iconSize = iconSize;
	ButtonGUI::buttonMargin = buttonMargin;
}

ButtonGUI::~ButtonGUI() {
	for (int i = 0; i < iconTextures.size(); i++) {
		UnloadTexture(iconTextures[i]);
	}
}

void ButtonGUI::addButton(std::string name, bool* buttonBool) {
	buttons.push_back({name, buttonBool});
	Image iconIMG = LoadImage((std::string("icons/") + name + std::string(".png")).c_str());
	ImageResize(&iconIMG, iconSize, iconSize);
	iconTextures.push_back(LoadTextureFromImage(iconIMG));
	UnloadImage(iconIMG);
}

void ButtonGUI::updateButtons() {
	float totalSize = buttonSize * buttons.size() +
		buttonMargin * (buttons.size() + 1);
	for (int i = 0; i < buttons.size(); i++) {
		float x = 20.f + (float)buttonMargin/2;
		float y = (float)(360 - totalSize/2 + buttonMargin + (buttonSize + buttonMargin) * i);
		Rectangle buttonRec = (Rectangle){x, y, (float)buttonSize, (float)buttonSize};
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), buttonRec)) {
			for (int j = 0; j < buttons.size(); j++) {
				*buttons[j].second = (i==j);
			}
		}

	}
}

void ButtonGUI::render() {
	float totalSize = buttonSize * buttons.size() +
		buttonMargin * (buttons.size() + 1);
	DrawRectangleRounded(
		(Rectangle){15.f, (float)(360 - totalSize/2), (float)(buttonSize + buttonMargin) + 10, totalSize},
		0.8, 20, (Color){130,130,130,255});
	for (int i = 0; i < buttons.size(); i++) {
		float x = 20.f + (float)buttonMargin/2;
		float y = (float)(360 - totalSize/2 + buttonMargin + (buttonSize + buttonMargin) * i);
		Rectangle buttonRec = (Rectangle){x, y, (float)buttonSize, (float)buttonSize};
		DrawRectangleRounded(buttonRec, 0.8, 20, *buttons[i].second ?  (Color){75,75,75,255} : (Color){100,100,100,255});
		if (*buttons[i].second || CheckCollisionPointRec(GetMousePosition(), buttonRec)) {
			DrawRectangleRoundedLinesEx(
				(Rectangle){x, y, (float)buttonSize, (float)buttonSize}, 0.8, 20, 2, BLACK);
		}
		DrawTexture(iconTextures[i], x + (float)buttonSize / 2 - (float)iconSize / 2, y + (float)buttonSize / 2 - (float)iconSize / 2, WHITE);
	}
}
