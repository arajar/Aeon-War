#pragma once
#include <SDL.h>
#include <vector>
#include "..\include\Img.h"
#include "..\include\Interfaces.h"
#include "..\include\Tile.h"

#define h_DESPLAZAMIENTO_HORIZONTAL 6
#define h_DESPLAZAMIENTO_VERTICAL 6

class Map : public IDrawable, public IClickable
{
public:
	Map(SDL_Surface* pScreen, int iWidth, int iHeight);
	~Map(void);

	int **getMap() { return _iMap; }
	void setTile(int iPosX, int iPosY, int iTile);
	int getTile(int iPosX, int iPosY);

	int genSpriteSheet(char* sFile, int iNumSprites, int iRows, int iCols);
	int getNumSprites() { return _iNumSprites; };
	Img* getSpriteSheet() { return _pSpriteSheet; };

	int genTiles();
	
	int loadMap(char* sFile);

	virtual void VDraw(int iPosX, int iPosY, SDL_Surface* pDestination = NULL, SDL_Rect* pClip = NULL);
	virtual void VHandleEvents(SDL_Event event);

private:
	int **_iMap;
	int _iNumTiles;
	std::vector<Tile*> _pTiles;

	SDL_Rect *_pClip;
	Img* _pSpriteSheet;
	Img* _pHighlight;
	int _iNumSprites;
	int _iSpriteSheetRows;
	int _iSpriteSheetCols;

	int _iWidth;
	int _iHeight;

	SDL_Surface* _pScreen;

	int _iScaledHeight;
	int _iHexSide;

	Point _offset;

};

