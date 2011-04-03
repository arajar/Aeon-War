#pragma once
#include "..\include\Tile.h"
#include "..\include\Gui.h"

Tile::Tile(SDL_Surface* pScreen)
{
	//_img = new Img();
	_coords.x = 0;
	_coords.y = 0;
	_coords.w = h_TILE_SIZE;
	_coords.h = h_TILE_SIZE;
	
	_pScreen = pScreen;
	_offset.x = 0;
	_offset.y = 0;
}


Tile::~Tile(void)
{
}

void Tile::VHandleEvents(SDL_Event event)
{
	if(event.type != SDL_MOUSEMOTION)
		return;

	int x = event.motion.xrel;
	int y = event.motion.yrel;
	updateCoords(x, y);
}

void Tile::VDraw(int iPosX, int iPosY, SDL_Surface* pDestination, SDL_Rect* pClip)
{
	if((UiState.iMouseX > _coords.x) && (UiState.iMouseX < _coords.x + _coords.w ) && (UiState.iMouseY > _coords.y ) && (UiState.iMouseY < _coords.y + _coords.h ))
	{
		SDL_FillRect(_pScreen, &_coords, SDL_MapRGB(_pScreen->format, 0,255,0));
	}
}