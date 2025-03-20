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
	public:
		ButtonGUI(int buttonSize, int iconSize, int buttonMargin);
		~ButtonGUI();
		void updateButtons();
		void addButton(std::string name, bool* buttonBool);
		void render();
};
