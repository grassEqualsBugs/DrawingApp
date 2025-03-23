#pragma once
#include "raylib.h"
#include <vector>

namespace ColorUtils {
	Color hsvToRGB(float h, float s, float v);
	std::vector<float> rgbToHSV(Color color);
}
