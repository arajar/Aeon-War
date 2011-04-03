#pragma once

struct UIState
{
	int iMouseX;
	int iMouseY;
	int iMouseDown;

	int iHotItem;
	int iActiveItem;

	int diff_x;
	int diff_y;
};

extern struct UIState UiState;

