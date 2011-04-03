#include "..\include\Img.h"


Img::Img(void)
{
}


Img::~Img(void)
{
}

int Img::loadImage(char* sFile)
{
	SDL_Surface* loadedImage = NULL;

	loadedImage = IMG_Load(sFile);
	if(loadedImage != NULL)
	{
		_pImg = SDL_DisplayFormatAlpha(loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	else
		return -1;

	return 0;
}

void Img::VDraw(int x, int y, SDL_Surface* pDestination, SDL_Rect* pClip)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(getSurface(), pClip, pDestination, &offset);
}