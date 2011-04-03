#pragma once
#include "..\include\Gui.h"
#include "..\include\GuiObject.h"
#include "..\include\Interfaces.h"

enum ACTION_MOVE
{
	ACTION_MOVE_RIGHT = 0,
	ACTION_MOVE_LEFT = 1,
	ACTION_MOVE_UP = 2,
	ACTION_MOVE_DOWN = 3
};

class GuiObject;
class GuiButton : public IHUD
{
public:
	GuiButton(int id, int x, int y, int w, int h);
	~GuiButton(void);

	virtual void VDraw(SDL_Surface* pDestination);
	virtual void VHandleEvents(SDL_Event event);

	void Attach(GuiObject* pObj) { _pObj = pObj; };
	bool CheckHit(int iMouseX, int iMouseY);

	void setAction(int iAction) { _iAction = iAction; };

	bool IsVisible() { return _bIsVisible; };
	void Show() { _bIsVisible = true; };
	void Hide() { _bIsVisible = false; };

private:
	SDL_Rect _bBox;
	Point _coords;

	GuiObject* _pObj;
	int _id;

	int _iAction;
	bool _bIsVisible;
	int r;
	int g;
	int b;

};

