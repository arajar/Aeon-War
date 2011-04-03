#include "..\include\GuiObject.h"


GuiObject::GuiObject(void)
{
	_img = new Img();
	_coords.x = 0;
	_coords.y = 0;

	_bIsLocked = false;
	_bIsVisible = true;
	_bIsWrapped = false;
}


GuiObject::~GuiObject(void)
{
	delete _img;
}


void GuiObject::VDraw(SDL_Surface* pDestination)
{
	SDL_Rect offset;
	offset.x = _coords.x;
	offset.y = _coords.y;

	if(_bIsVisible)
		SDL_BlitSurface(getImg()->getSurface(), NULL, pDestination, &offset);
}

void GuiObject::setImg(char* sFile)
{
	_img->loadImage(sFile);
}

void GuiObject::VHandleEvents(SDL_Event event)
{

}

void GuiObject::Wrap(int iAction)
{
	if(!IsWrapped() && !IsLocked())
	{
		switch(iAction)
		{
			case ACTION_MOVE_RIGHT:
			{
				_coords.x = 780;
				break;
			}
			case ACTION_MOVE_LEFT:
			{
				_bBox.x = 3;
				break;
			}
		}
	}
}