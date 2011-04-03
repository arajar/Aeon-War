#include "..\include\Map.h"


Map::Map(SDL_Surface *pScreen, int iWidth, int iHeight)
{
	_pClip = NULL;
	_pSpriteSheet = NULL;
	_pScreen = pScreen;

	_iWidth = iWidth;
	_iHeight = iHeight;

	_iNumTiles = iWidth * iHeight;
	_iMap = new int*[iHeight];
	for(int i = 0; i < iWidth; i++)
		_iMap[i] = new int[iWidth];

	_pHighlight = new Img();
	_pHighlight->loadImage("img/hex-highlight.png");
}


Map::~Map(void)
{
}

void Map::setTile(int iPosX, int iPosY, int iTile)
{
	getMap()[iPosX][iPosY] = iTile;
}

int Map::getTile(int iPosX, int iPosY)
{
	return getMap()[iPosX][iPosY];
}

int Map::genSpriteSheet(char* sFile, int iNumSprites, int iRows, int iCols)
{
	int iNum = 0;
	_iNumSprites = iNumSprites;
	_iSpriteSheetRows = iRows;
	_iSpriteSheetCols = iCols;

	_pSpriteSheet = new Img();
	if(getSpriteSheet()->loadImage(sFile) == -1)
		return -1;


	_pClip = new SDL_Rect[iNumSprites];

	for(int i = 0; i < _iSpriteSheetCols; i++)
	{
		for(int j = 0; j < _iSpriteSheetRows; j++)
		{
			_pClip[iNum].x = (h_DESPLAZAMIENTO_HORIZONTAL * (j + 1)) + (h_TILE_SIZE * j);
			_pClip[iNum].y = (h_DESPLAZAMIENTO_VERTICAL * (i + 1) + (h_TILE_SIZE * i));
			_pClip[iNum].w = h_TILE_SIZE;
			_pClip[iNum].h = h_TILE_SIZE;

			iNum++;
		}
	}

	_iScaledHeight = h_TILE_SIZE * 1;
	_iHexSide = _iScaledHeight / 2;

	/* TEMPORAL hasta que tenga el formato de mapa hecho */
	for(int x = 0; x < _iHeight; x++)
	{
		for(int y = 0; y < _iWidth; y++)
		{
			int a = rand() % 8;
			_iMap[x][y] = a;
		}
	}

	genTiles();
	
	return 0;
}

int Map::genTiles()
{
	for(int x = 0; x < _iHeight; x++)
	{
		for(int y = 0; y < _iWidth; y++)
		{
			int tx = x * h_TILE_SIZE;
			int ty = y * h_TILE_SIZE;
			Tile *pTile = new Tile(_pScreen);
			pTile->setCoords(tx, ty);
			pTile->setMatrixPos(x, y);
			_pTiles.push_back(pTile);
		}
	}
	return 0;
}


int Map::loadMap(char* sFile)
{
	return 0;
}

void Map::VDraw(int iPosX, int iPosY, SDL_Surface* pDestination, SDL_Rect* pClip)
{
	_offset.x = iPosX;
	_offset.y = iPosY;
	int x = 0;
	int y = 0;
	std::vector<Tile*>::iterator it;
	for(it = _pTiles.begin();
		it != _pTiles.end();
		it++)
	{
		x = (*it)->getCoords().x;
		y = (*it)->getCoords().y;
		getSpriteSheet()->VDraw(x, y,			
			_pScreen, &_pClip[_iMap[(*it)->getMatrixPos().x][(*it)->getMatrixPos().y]]);

		(*it)->VDraw(iPosX, iPosY);
	}
}

void Map::VHandleEvents(SDL_Event event)
{

	int a = 0;
	std::vector<Tile*>::iterator it;
	for(it = _pTiles.begin();
		it != _pTiles.end();
		it++, a++)
	{
		if(a == 10)
			int f = 213;
		
		//(*it)->updateCoords(x, y);
		(*it)->VHandleEvents(event);
	}
}