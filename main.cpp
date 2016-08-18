#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "common.h"
#include "layout.h"
#include "editor.h"
#include "clickcontrol.h"


int main ( int argc, char** argv )
{
	using namespace iso;
// Launch our App, get screen and renderer
	cfg.init();
// load an image
	AreaMap* amap = new AreaMap("Map", 64, 64, 8, 8);
	Editor* editor = new Editor(amap, cfg.renderer, cfg.screen);

	ClickControl* ccontrol = new ClickControl(cfg.renderer, editor, cfg.screen);
    // program main loop
    bool done = false;
    while (!done)
    {
    // drawing
	SDL_SetRenderDrawColor(cfg.renderer, 119, 136, 153, 255);
    SDL_RenderClear(cfg.renderer);
	//qqSDL_RenderCopy(cfg.renderer, texture, NULL, NULL);
    //SDL_SetRenderDrawColor(cfg.renderer, 0, 255, 0, 255);
	editor->renderGrid();

	ccontrol->doRender();
	editor->listTileset(amap->layers[0].tileset);
	SDL_RenderPresent(cfg.renderer);

        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
            // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

            // check for keypresses
            case SDL_KEYDOWN:
			{
				if (event.key.keysym.mod == KMOD_LSHIFT)
				{
					switch(event.key.keysym.sym)
					{
						case SDLK_UP:
							editor->resizeLayerGrid(0, 1);
							break;
						default:
							break;
					}
				}
				else
				{
					switch (event.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						done = true;
						break;
					case SDLK_w:
						editor->amap->offsetY += 10;
						break;
					case SDLK_s:
						editor->amap->offsetY -=10;
						break;
					case SDLK_a:
						editor->amap->offsetX +=10;
						break;
					case SDLK_d:
						editor->amap->offsetX -= 10;
						break;
					case SDLK_q:
						editor->rotateCurrent(-90);
						break;
					case SDLK_e:
						editor->rotateCurrent(90);
						break;
					case SDLK_UP:
						editor->moveCurrent(0, -1);
						break;
					case SDLK_DOWN:
						editor->moveCurrent(0, 1);
						break;
					case SDLK_LEFT:
						editor->moveCurrent(-1, 0);
						break;
					case SDLK_RIGHT:
						editor->moveCurrent(1,0);
						break;
					case SDLK_z:
						editor->amap->zoomX -= 4;
						editor->amap->zoomY -= 4;
						break;
					case SDLK_x:
						editor->amap->zoomX += 4;
						editor->amap->zoomY += 4;
						break;
					case SDLK_MINUS:
						editor->setCurrentTile(0);
						break;
					case SDLK_0:
						editor->setCurrentTile(10);
						break;
					case SDLK_1:
						editor->setCurrentTile(1);
						break;
					case SDLK_2:
						editor->setCurrentTile(2);
						break;
					case SDLK_3:
						editor->setCurrentTile(3);
						break;
					case SDLK_4:
						editor->setCurrentTile(4);
						break;
					case SDLK_5:
						editor->setCurrentTile(5);
						break;
					case SDLK_6:
						editor->setCurrentTile(6);
						break;
					case SDLK_7:
						editor->setCurrentTile(7);
						break;
					case SDLK_8:
						editor->setCurrentTile(8);
						break;
					case SDLK_9:
						editor->setCurrentTile(9);
						break;
					case SDLK_c:
						editor->resizeLayerGrid(0,1);
						break;
					case SDLK_v:
						editor->resizeLayerGrid(0, -1);
						break;
					case SDLK_b:
						editor->resizeLayerGrid(1, 0);
						break;
					case SDLK_n:
						editor->resizeLayerGrid(-1,0);
						break;



					} // case keydown
				case SDL_MOUSEBUTTONDOWN:
					{
					ccontrol->doInput(event.button.x, event.button.y);
					break;

					} // case buttondown
				}
				}
			} // end switch
        } // end of message processing
    } // end main loop

    SDL_DestroyRenderer(cfg.renderer);
    SDL_DestroyWindow(cfg.screen);

    SDL_Quit();
    return 0;
}
