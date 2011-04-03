#pragma once
#include "..\include\Img.h"
#include "..\include\Interfaces.h"
#include "..\include\GuiButton.h"

class GuiObject : public IHUD
{
public:
	GuiObject(void);
	~GuiObject(void);

	virtual void VDraw(SDL_Surface* pDestination);
	virtual void VHandleEvents(SDL_Event event);

	inline void setCoords(int iPosX, int iPosY) { _coords.x = iPosX; _coords.y = iPosY; };
	inline void setCoords(Point point) { _coords = point; };
	inline Point getCoords() { return _coords; };

	bool IsLocked() { return _bIsLocked; };
	void Lock() { _bIsLocked = true; };
	void Unlock() { _bIsLocked = false; };

	bool IsVisible() { return _bIsVisible; };
	void Show() { _bIsVisible = true; };
	void Hide() { _bIsVisible = false; };

	bool IsWrapped() { return _bIsWrapped; };
	void Wrap() { _bIsWrapped = true; };
	void Wrap(int iSide);
	void Unwrap() { _bIsWrapped = false; };

	void setImg(Img* img) { _img = img; };
	void setImg(char* sFile);
	Img* getImg() { return _img; };

private:

	Img* _img;
	Point _coords;
	bool _bIsLocked;
	bool _bIsWrapped;
	bool _bIsVisible;

	SDL_Rect _bBox;	
};

