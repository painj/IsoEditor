#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "editor.h"

#include "clickcontrol.h"

iso::ClickControl::ClickControl(SDL_Renderer* rend, Editor* ed, SDL_Window* win)
{
	renderer = rend;
	editor = ed;
	window = win;

	int winw, winh;

	SDL_GetWindowSize(window, &winw, &winh);

	int botrow = winh - 66;
	int leftside = winw - (2+MenuBarSize * 5);

	SDL_Texture* menuButton = MenuButton("images/gui/glassPanel.png", "images/gui/menuGrid.png");
	MenuItem mi {{"MenuGrid", "Open the Menu", false}, menuButton,
					{2, 2, MenuButtonSize, MenuButtonSize}, true, false};
	add(mi);

	SDL_Texture* exitButton = MenuButton("images/gui/glassPanel.png", "images/gui/exit.png");
	MenuItem ei {{"Exit", "Exits the App", false}, exitButton,
				{2+MenuButtonSize, 2, MenuButtonSize, MenuButtonSize}, false, false};
	add(ei);

	SDL_Texture* leftButton = MenuButton("images/gui/glassPanel.png", "images/gui/left.png");
	MenuItem lb {{"LeftButton", "LeftButton", false}, leftButton,
					{2+MenuBarSize, botrow, MenuBarSize, MenuBarSize}, true, false};
	add(lb);

	SDL_Texture* downButton = MenuButton("images/gui/glassPanel.png", "images/gui/down.png");
	MenuItem db {{"DownButton", "DownButton", false}, downButton,
				{2+MenuBarSize*2, botrow, MenuBarSize, MenuBarSize}, true, false};
	add(db);

	SDL_Texture* upButton = MenuButton("images/gui/glassPanel.png", "images/gui/up.png");
	MenuItem ub {{"UpButton", "UpButton", false}, upButton,
				{2+MenuBarSize*3, botrow, MenuBarSize, MenuBarSize}, true, false};
	add(ub);

	SDL_Texture* rightButton = MenuButton("images/gui/glassPanel.png", "images/gui/right.png");
	MenuItem rb {{"RightButton", "RightButton", false}, rightButton,
				{2+MenuBarSize*4, botrow, MenuBarSize, MenuBarSize}, true, false};
	add(rb);

	SDL_Texture* leftButton2 = MenuButton("images/gui/glassPanel.png", "images/gui/left.png");
	MenuItem lb2 {{"LeftButton2", "LeftButton2", false}, leftButton2,
					{leftside, botrow, MenuBarSize, MenuBarSize}, true, false};
	add(lb2);

	SDL_Texture* downButton2 = MenuButton("images/gui/glassPanel.png", "images/gui/down.png");
	MenuItem db2 {{"DownButton2", "DownButton2", false}, downButton2,
				{leftside + 2+MenuBarSize, botrow, MenuBarSize, MenuBarSize}, true, false};
	add(db2);

	SDL_Texture* upButton2 = MenuButton("images/gui/glassPanel.png", "images/gui/up.png");
	MenuItem ub2 {{"UpButton2", "UpButton2", false}, upButton2,
				{leftside + 2+MenuBarSize*2, botrow, MenuBarSize, MenuBarSize}, true, false};
	add(ub2);

	SDL_Texture* rightButton2 = MenuButton("images/gui/glassPanel.png", "images/gui/right.png");
	MenuItem rb2 {{"RightButton2", "RightButton2", false}, rightButton2,
				{leftside + 2+MenuBarSize*3, botrow, MenuBarSize, MenuBarSize}, true, false};
	add(rb2);

	SDL_Texture* zoomIn = MenuButton("images/gui/glassPanel.png", "images/gui/zoomIn.png");
	MenuItem zi {{"ZoomIn", "ZoomIn", false}, zoomIn,
					{2, 6 + MenuButtonSize, MenuButtonSize, MenuButtonSize}, true, false};
	add(zi);

	SDL_Texture* zoomOut = MenuButton("images/gui/glassPanel.png", "images/gui/zoomOut.png");
	MenuItem zo {{"ZoomOut", "ZoomOut", false}, zoomOut,
					{2, 6 + MenuButtonSize*2, MenuButtonSize, MenuButtonSize}, true, false};
	add(zo);
}

iso::ClickControl::~ClickControl()
{
}

SDL_Texture* iso::ClickControl::MenuButton(const char* bgimage, const char* fgimage, int w, int h)
{
	SDL_Texture* button = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
	SDL_Texture* bgImage = loadImage(bgimage);
	SDL_Texture* fgImage = loadImage(fgimage);

	SDL_SetRenderTarget(renderer, button);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(fgImage, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(bgImage, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(button, SDL_BLENDMODE_BLEND);
	SDL_RenderCopy(renderer, bgImage, NULL, NULL);
	SDL_RenderCopy(renderer, fgImage, NULL, NULL);
	SDL_SetRenderTarget(renderer, NULL);
	SDL_DestroyTexture(bgImage);
	SDL_DestroyTexture(fgImage);
	return button;
}

iso::SettingsPanel* iso::ClickControl::createSettingsPanel(std::string head, const char* bgfile, const char* fgfile, int x, int y, int w, int h)
{
		SettingsPanel sp;
		sp.heading = head;
		sp.bgFilename = bgfile;
		sp.fgFilename = fgfile;
		sp.panelRect = {x, y, w, h};
		sp.headingRect = {0, 0, w/4, 16};
		sp.show = true;
		sp.minimized = false;
		sp.panel = MenuButton(bgfile, fgfile,w, h);

}

void iso::ClickControl::renderMenuBar()
{

}

void iso::ClickControl::add(MenuItem menuItem)
{
	controlRegistery.push_back(menuItem);
}

void iso::ClickControl::doRender()
{
	for (int i = 0; i < controlRegistery.size();i++)
	{
		if (controlRegistery[i].show)
			SDL_RenderCopy(renderer, controlRegistery[i].button, NULL, &controlRegistery[i].rect);

	}
}

void iso::ClickControl::doInput(int x, int y)
{
	SDL_Point clickpos {x, y};
	for (int i = 0; i < controlRegistery.size();i++)
	{
		if (controlRegistery[i].show)
			if (SDL_PointInRect(&clickpos, &controlRegistery[i].rect))
			{
				if (controlRegistery[i].pressed != true)
				{
					controlRegistery[i].pressed = true;
					controlRegistery[i].action.active = true;
				}
				else
					controlRegistery[i].pressed = false;


				std::cout << "Mouse Click at: " << clickpos.x << "," << clickpos.y << " on " << controlRegistery[i].action.name << std::endl;
				updateActions();
			}

	}
}

void iso::ClickControl::updateActions()
{
	for (int i = 0; i < controlRegistery.size();i++)
	{
		bool actionDone = false;
		if (controlRegistery[i].action.active)
			actionDone = doAction(controlRegistery[i].action.name);
		if (actionDone)
			controlRegistery[i].action.active = false;
	}

}

bool iso::ClickControl::doAction(std::string name)
{
	if (name == "MenuGrid")
	{
		for (int i = 0; i < controlRegistery.size();i++)
			if (controlRegistery[i].action.name == "Exit")
				if (controlRegistery[i].show == true)
					controlRegistery[i].show = false;
				else
					controlRegistery[i].show = true;
		return false;
	}
	else if (name == "Exit")
	{
		SDL_Quit();
		return true;
	}
	else if (name == "LeftButton")
	{
		editor->amap->offsetX += 10;
		return true;
	}
	else if (name =="RightButton")
	{
		editor->amap->offsetX -= 10;
		return true;
	}
	else if (name =="UpButton")
	{
		editor->amap->offsetY += 10;
		return true;
	}
	else if (name == "DownButton")
	{
		editor->amap->offsetY -= 10;
		return true;
	}
	else if (name == "LeftButton2")
	{
		editor->moveCurrent(-1, 0);
		return true;
	}
	else if (name == "RightButton2")
	{
		editor->moveCurrent(1, 0);
		return true;
	}
	else if (name == "UpButton2")
	{
		editor->moveCurrent(0, -1);
		return true;
	}
	else if (name == "DownButton2")
	{
		editor->moveCurrent(0, 1);
		return true;
	}
	else if (name == "ZoomIn")
	{
		editor->amap->zoomX += 4;
		editor->amap->zoomY += 2;
		return true;
	}
	else if (name == "ZoomOut")
	{
		editor->amap->zoomX -= 4;
		editor->amap->zoomY -= 2;
		return true;
	}

	else
		return false;

}

