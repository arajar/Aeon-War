#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "..\include\Interfaces.h"

struct Point
{
	int x;
	int y;
};

class Img : public IDrawable
{
public:
	Img();
	~Img(void);

	int loadImage(char* sFile);
	SDL_Surface* getSurface() { return _pImg; };

	virtual void VDraw(int x, int y, SDL_Surface* pDestination = NULL, SDL_Rect* pClip = NULL);

private:
	SDL_Surface* _pImg;
	char* _sFile;
};

