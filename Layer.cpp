#include "include/Layer.hpp"

Layer::Layer(int width, int height) {
	renderTexture = LoadRenderTexture(width, height);
	BeginTextureMode(renderTexture);
	ClearBackground(WHITE);
	EndTextureMode();
}

void Layer::drawStroke(Stroke stroke) {
	strokes.push_back(stroke);
	BeginTextureMode(renderTexture);
	stroke.render();
	EndTextureMode();
}

void Layer::removeLastStroke() {
	if (strokes.size() == 0) return;
	Brush b = strokes[strokes.size() - 1].getBrush();
	b.setColor(WHITE);
	strokes[strokes.size() - 1].setBrush(b);
	BeginTextureMode(renderTexture);
	strokes[strokes.size() - 1].render();
	strokes.pop_back();
	for (Stroke s : strokes)
		s.render();
	EndTextureMode();
}

void Layer::restart() {
	strokes.clear();
	strokes.shrink_to_fit();
	BeginTextureMode(renderTexture);
	ClearBackground(WHITE);
	EndTextureMode();
}

void Layer::fill(Vector2 mousePosition, Color fillColor) {
    BeginTextureMode(renderTexture);

    // Get texture data as an image
    Image image = LoadImageFromTexture(renderTexture.texture);
    Color* pixels = LoadImageColors(image);

    int width = image.width;
    int height = image.height;
    int x = (int)mousePosition.x;
    int y = height - (int)mousePosition.y;

    if (x < 0 || x >= width || y < 0 || y >= height) {
        UnloadImageColors(pixels);
        UnloadImage(image);
        EndTextureMode();
        return;
    }

    Color targetColor = pixels[y * width + x];
    if (ColorUtils::colorEqual(targetColor, fillColor)) { // Avoid unnecessary fills
        UnloadImageColors(pixels);
        UnloadImage(image);
        EndTextureMode();
        return;
    }

    // Implement a stack-based flood fill (iterative to avoid stack overflow)
    std::stack<Vector2> stack;
    stack.push({(float)x, (float)y});

    while (!stack.empty()) {
        Vector2 pos = stack.top();
        stack.pop();

        int px = (int)pos.x;
        int py = (int)pos.y;

        if (px < 0 || px >= width || py < 0 || py >= height) continue;
        if (!ColorUtils::colorEqual(pixels[py * width + px], targetColor)) continue;

        pixels[py * width + px] = fillColor;

        stack.push({(float)(px + 1), (float)py});
        stack.push({(float)(px - 1), (float)py});
        stack.push({(float)px, (float)(py + 1)});
        stack.push({(float)px, (float)(py - 1)});
    }

    // Update texture with modified image
    UpdateTexture(renderTexture.texture, pixels);

    // Cleanup
    UnloadImageColors(pixels);
    UnloadImage(image);

    EndTextureMode();
}

void Layer::render() {
	DrawTextureRec(
	    renderTexture.texture,
	    (Rectangle){0, 0, (float)renderTexture.texture.width, -(float)renderTexture.texture.height},
	    (Vector2){0, 0},
	    WHITE
	);
}
