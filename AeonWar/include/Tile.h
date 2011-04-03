#pragma once
#include <vector>
#include "..\include\Interfaces.h"
#include "..\include\Img.h"

#define h_TILE_SIZE 60

enum TileProperties
{
	WALKABLE = 0,
	FLYABLE = 1,
	SWIMMABLE = 2
};

class Tile : public IClickable, public IDrawable
{
public:
	Tile(SDL_Surface* pScreen);
	~Tile(void);

	//virtual void VDraw(int iPosX, int iPosY, SDL_Surface* pDestination = NULL, SDL_Rect* pClip = NULL);
	void VHandleEvents(SDL_Event event);
	void VDraw(int iPosX, int iPosY, SDL_Surface* pDestination = NULL, SDL_Rect* pClip = NULL);

//	void addProperty(int iProp);
//	std::vector<int> getProperties() { return _vProperties; };

//	void setImg(Img* img) { _img = img; };
//	Img* getImg() { return _img; };

	void setCoords(int iPosX, int iPosY) { _coords.x = iPosX; _coords.y = iPosY; };
	void setCoords(Point point)
	{
		_coords.x = point.x;
		_coords.y = point.y;
	};

	Point getCoords()
	{ 
		Point p;
		p.x = _coords.x;
		p.y = _coords.y;
		return p; 
	};

	void updateCoords(int x, int y)
	{
		_coords.x += x;
		_coords.y += y;
	};

	SDL_Rect getBBox() { return _coords; };

	Point getMatrixPos() { return _map; };
	void setMatrixPos(int x, int y) { _map.x = x; _map.y = y; };
	void setMatrixPos(Point point) { _map = point; };

private:
//	std::vector<int> _vProperties;
//	Img* _img;

	SDL_Rect _coords;
	Point _offset;
	Point _map;

	Point _n;

	SDL_Surface* _pScreen;
};

