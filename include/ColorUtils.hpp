#pragma once
#include "raylib.h"
#include <vector>

namespace ColorUtils {
	Color hsvToRGB(std::vector<float> hsv);
	std::vector<float> rgbToHSV(Color color);
	bool colorEqual(Color a, Color b);
}
