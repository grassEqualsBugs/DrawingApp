#include "include/ButtonGUI.hpp"
#include "include/raylib.h"
#include "include/Stroke.hpp"
#include "include/Layer.hpp"
#include "include/ColorPickerGUI.hpp"
#include <vector>

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const char* WINDOW_TITLE = "";

// Layers
std::vector<Layer> layers;
int currLayerIdx;

// User State
Stroke userStroke;
bool isPen = true;
bool isEraser = false;
bool isFill = false;

// Brush
Color brushColor = BLACK;
int brushThickness = 5;
int eraserThickness = 30;
Brush currentBrush(brushThickness, BLACK);

// Buttons GUI
ButtonGUI buttonsGUI(64, 40, 10, WINDOW_HEIGHT / 2);

void handleKeyboardShortcuts() {
	if (IsKeyPressed(KEY_E)) { // eraser
		isEraser = true;
		isPen = false;
	} else if (IsKeyPressed(KEY_P)) { // pen
		isPen = true;
		isEraser = false;
	} else if (IsKeyPressed(KEY_R)) { // restart
		layers[currLayerIdx].clearStrokes();
	} else if (IsKeyPressed(KEY_Z)) { // undo
		layers[currLayerIdx].removeLastStroke();
	}
}

void updateCurrentLayer() {
	if (isPen) {
		currentBrush.setColor(brushColor);
		currentBrush.setSize(brushThickness);
	} else if (isEraser) {
		currentBrush.setColor(WHITE);
		currentBrush.setSize(eraserThickness);
	}

	Vector2 mousePosition = GetMousePosition();
	Vector2 mouseMovement = GetMouseDelta();

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		userStroke = Stroke(mousePosition, currentBrush);
	} else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
		layers[currLayerIdx].drawStroke(userStroke);
		userStroke = Stroke();
	}
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
		userStroke.update(mousePosition);
	}
}

int main() {
	SetConfigFlags(FLAG_VSYNC_HINT);
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	SetTargetFPS(120);

	ColorPickerGUI colorPickerGUI(50, (Vector2){(float)WINDOW_WIDTH / 2, (float)WINDOW_HEIGHT / 2}, RED);

	layers.push_back(Layer(WINDOW_WIDTH, WINDOW_HEIGHT));
	currLayerIdx = 0;

	buttonsGUI.addButton("pen", &isPen);
	buttonsGUI.addButton("eraser", &isEraser);
	// buttonsGUI.addButton("fill", &isFill);

	while (!WindowShouldClose()) {
		// --- UPDATES --- //
		handleKeyboardShortcuts();
		updateCurrentLayer();
		buttonsGUI.updateButtons();

		// --- RENDERING --- //
		for (Layer layer : layers)
			layer.updateRenderTexture();
		BeginDrawing();
		ClearBackground(WHITE);
		for (Layer layer : layers)
			layer.render();
		userStroke.render();
		colorPickerGUI.render();
		buttonsGUI.render();
		EndDrawing();
	}
	CloseWindow();

	return 0;
}
