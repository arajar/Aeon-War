#include "..\include\GuiButton.h"

UIState UiState;

GuiButton::GuiButton(int id, int x, int y, int w, int h)
{
	_bBox.x = x;
	_bBox.y = y;
	_bBox.w = w;
	_bBox.h = h;

	_coords.x = x;
	_coords.y = y;

	r = 255;
	g = 0;
	b = 255;

	_id = id;
}


GuiButton::~GuiButton(void)
{
}

void GuiButton::VDraw(SDL_Surface* pDestination)
{
#ifdef _DEBUG
	if(UiState.iHotItem == _id)
	{
		if(UiState.iActiveItem == _id)
		{
			r = 0;
			g = 255;
			b = 255;
		}
		else
		{
			r = 255;
			g = 0;
			b = 0;
		}
	}
	else
	{
		r = 255;
		g = 0;
		b = 255;
	}
#endif
	if(IsVisible())
		SDL_FillRect(pDestination, &_bBox, SDL_MapRGBA(pDestination->format, r, g, b, 100));
}

void GuiButton::VHandleEvents(SDL_Event event)
{
	int x = 0;
	int y = 0;
	
	if(CheckHit(UiState.iMouseX, UiState.iMouseY))
	{
		UiState.iHotItem = _id;
		if(UiState.iActiveItem == 0 && UiState.iMouseDown)
			UiState.iActiveItem = _id;
		
		if(UiState.iMouseDown == 0 &&
			UiState.iHotItem == _id &&
			UiState.iActiveItem == _id)
		{
			if(!_pObj->IsLocked())
			{
				_pObj->Lock();
			}
#ifdef _DEBUG
			r = 255;
			g = 0;
			b = 255;
#endif
		}
	}

	if(_pObj->IsLocked())
	{
		if(!_pObj->IsWrapped())
		{
			if(_iAction == ACTION_MOVE_RIGHT)
			{
				if(_pObj->getCoords().x >= 780)
				{
					_pObj->Unlock();
					_pObj->Wrap();
					_bBox.x = 780;
				}
				else
					_pObj->setCoords(_pObj->getCoords().x + 1, _pObj->getCoords().y);
			}

			if(_iAction == ACTION_MOVE_LEFT)
			{
				int x = _pObj->getCoords().x;
				if(_pObj->getCoords().x <= -32)
				{
					_pObj->Unlock();
					_pObj->Wrap();
					_bBox.x = 3;
				}
				else
					_pObj->setCoords(_pObj->getCoords().x - 1, _pObj->getCoords().y);
			}

		}

		if(_pObj->IsWrapped())
		{
			if(_iAction == ACTION_MOVE_RIGHT)
			{
				if(_pObj->getCoords().x <= 650)
				{
					_pObj->Unlock();
					_pObj->Unwrap();
					_bBox.x = 650;
				}
				else
					_pObj->setCoords(_pObj->getCoords().x - 1, _pObj->getCoords().y);
			}

			if(_iAction == ACTION_MOVE_LEFT)
			{
				if(_pObj->getCoords().x >= 0)
				{
					_pObj->Unlock();
					_pObj->Unwrap();
					_bBox.x = 35;
				}
				else
					_pObj->setCoords(_pObj->getCoords().x + 1, _pObj->getCoords().y);
			}
		}
	}
			
}

bool GuiButton::CheckHit(int iMouseX, int iMouseY)
{
	if((iMouseX > _bBox.x) && (iMouseX < _bBox.x + _bBox.w ) && (iMouseY > _bBox.y ) && (iMouseY < _bBox.y + _bBox.h ))
		return true;

	return false;
}
