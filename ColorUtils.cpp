#include "include/ColorUtils.hpp"

namespace ColorUtils {
	Color hsvToRGB(std::vector<float> hsv) {
		float h = hsv[0], s = hsv[1], v = hsv[2];
	    float r = 0, g = 0, b = 0;
	    int hi = static_cast<int>(h / 60) % 6;
	    float f = (h / 60.0f) - hi;
	    float p = v * (1 - s);
	    float q = v * (1 - f * s);
	    float t = v * (1 - (1 - f) * s);

	    switch (hi) {
	        case 0: r = v, g = t, b = p; break;
	        case 1: r = q, g = v, b = p; break;
	        case 2: r = p, g = v, b = t; break;
	        case 3: r = p, g = q, b = v; break;
	        case 4: r = t, g = p, b = v; break;
	        case 5: r = v, g = p, b = q; break;
	    }

	    return (Color){
	        static_cast<unsigned char>(r * 255),
	        static_cast<unsigned char>(g * 255),
	        static_cast<unsigned char>(b * 255),
	        static_cast<unsigned char>(255)
	    };
	}

	std::vector<float> rgbToHSV(Color color) {
	    float r = (int)color.r / 255.0f;
	    float g = (int)color.g / 255.0f;
	    float b = (int)color.b / 255.0f;
	    float maxVal = std::max({r, g, b});
	    float minVal = std::min({r, g, b});
	    float delta = maxVal - minVal;

	    float h = 0.0f, s = 0.0f, v = maxVal;

	    if (delta > 0.0f) {
	        if (maxVal == r) {
	            h = 60.0f * fmod(((g - b) / delta), 6);
	        } else if (maxVal == g) {
	            h = 60.0f * (((b - r) / delta) + 2);
	        } else if (maxVal == b) {
	            h = 60.0f * (((r - g) / delta) + 4);
	        }

	        if (maxVal > 0.0f) {
	            s = delta / maxVal;
	        }
	    }

	    if (h < 0.0f) {
	        h += 360.0f;
	    }

	    return {h, s, v};
	}
}
