#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <vector>
#include "..\include\Gui.h"
#include "..\include\Map.h"
#include "..\include\GuiObject.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

std::vector<IDrawable*> lista;
std::vector<IDrawable*>::iterator it;

std::vector<IHUD*> listaHud;
std::vector<IHUD*>::iterator itHud;

void PreparaUI();

int main( int argc, char* args[] )
{
	SDL_Surface* pScreen = NULL;
	SDL_Event event;
	bool quit = false;
	Map* pMap = NULL;

    SDL_Init( SDL_INIT_EVERYTHING );
    
	pScreen = SDL_SetVideoMode(800, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	
	if(pScreen == NULL)
	{
		return 1;
	}

	UiState.iActiveItem = 0;
	UiState.iHotItem = 0;
	UiState.iMouseDown = 0;
	UiState.iMouseX = 0;
	UiState.iMouseY = 0;

	SDL_WM_SetCaption("Aeon War", NULL);

	pMap = new Map(pScreen, 60, 60);
	pMap->genSpriteSheet("img/Tiles_Fondo_SpriteSheet_templatev2.png", 60, 10, 6);
	lista.push_back(pMap);

	PreparaUI();
	
	int vert = 0;
	int hor = 0;
	while(quit == false)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
				quit = true;
		}

		switch(event.type)
		{
			case SDL_MOUSEMOTION:
			{
				UiState.iMouseX = event.motion.x;
				UiState.iMouseY = event.motion.y;
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				if(event.button.button == 1)
					UiState.iMouseDown = 1;
				break;
			}
			case SDL_MOUSEBUTTONUP:
			{
				if(event.button.button == 1)
					UiState.iMouseDown = 0;
				break;
			}
		}
		int x = 0;
		int y = 0;
		
		SDL_FillRect(pScreen, &pScreen->clip_rect, SDL_MapRGB(pScreen->format, 0, 0, 0) );
		
		if(SDL_GetRelativeMouseState(&x, &y) & SDL_BUTTON_LMASK)
		{
			int old_x = hor;
			int old_v = vert;
			hor += x;
			vert += y;

			if(old_x != hor || old_v != vert)
				pMap->VHandleEvents(event);
		}
		
		for(it = lista.begin();
			it != lista.end();
			it++)
		{
			(*it)->VDraw(hor, vert);
		}
		
		UiState.iHotItem = 0;

		for(itHud = listaHud.begin();
			itHud != listaHud.end();
			itHud++)
		{
			(*itHud)->VHandleEvents(event);
			(*itHud)->VDraw(pScreen);
		}

		if(UiState.iMouseDown == 0)
		{
			UiState.iActiveItem = 0;
		}
		else
		{
			if(UiState.iActiveItem == 0)
				UiState.iActiveItem = -1;
		}

		if(SDL_Flip(pScreen) == -1)
		{
			return 1;
		}

	}

    SDL_Quit();
    
    return 0;    
}


void PreparaUI()
{
	GuiObject* pMenuAbajo = new GuiObject();
	pMenuAbajo->setImg("img/HUD/ventana_texto_mision.png");
	pMenuAbajo->setCoords(100, 330);
	//listaHud.push_back(pMenuAbajo);

	GuiObject* pMenuIzq = new GuiObject();
	pMenuIzq->setImg("img/HUD/menu_izq.png");
	pMenuIzq->setCoords(0, 0);
	listaHud.push_back(pMenuIzq);

	GuiObject* pMenuDer = new GuiObject();
	pMenuDer->setImg("img/HUD/ventana_derecha.png");
	pMenuDer->setCoords(650, 0);
	listaHud.push_back(pMenuDer);

	GuiObject* pMenuArriba = new GuiObject();
	pMenuArriba->setImg("img/HUD/menu_arriba.png");
	pMenuArriba->setCoords(130, 0);
	listaHud.push_back(pMenuArriba);

	GuiButton* pBotonIzq = new GuiButton(222, 35, 187, 17, 100);
	pBotonIzq->Attach(pMenuIzq);
	pBotonIzq->setAction(ACTION_MOVE_LEFT);
	pBotonIzq->Hide();
	listaHud.push_back(pBotonIzq);

	GuiButton* pBotonDer = new GuiButton(333, 650, 187, 17, 100);
	pBotonDer->Attach(pMenuDer);
	pBotonDer->setAction(ACTION_MOVE_RIGHT);
	pBotonDer->Hide();
	listaHud.push_back(pBotonDer);
}