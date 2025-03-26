#pragma once
#include <vector>
#include <string>
#include <utility>

#include "raylib.h"

class ButtonGUI {
	private:
		std::vector<std::pair<std::string, bool*>> buttons;
		std::vector<Texture2D> iconTextures;
		int buttonSize;
		int iconSize;
		int buttonMargin;
		int screenHalfway;
	public:
		ButtonGUI(int buttonSize, int iconSize, int buttonMargin, int screenHalfway);
		~ButtonGUI();
		void updateButtons();
		Rectangle getTotalRectangle();
		void addButton(std::string name, bool* buttonBool);
		void render();
};
