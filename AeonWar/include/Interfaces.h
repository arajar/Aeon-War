#pragma once
#include <SDL.h>

class IDrawable
{
public:
	virtual void VDraw(int iPosX, int iPosY, SDL_Surface* pDestination = NULL, SDL_Rect* pClip = NULL) = 0;
};

class IHUD
{
public:
	virtual void VDraw(SDL_Surface* pDestination) = 0;
	virtual void VHandleEvents(SDL_Event event) = 0;
};

class IClickable
{
public:
	virtual void VHandleEvents(SDL_Event event) = 0;
};