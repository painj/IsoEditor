#ifndef _EDITOR_H_
#define _EDITOR_H_
#include <unordered_map>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "layout.h"

namespace iso
{
extern SDL_Texture* loadImage(const char* name);



class Editor
{
	public:
	AreaMap* amap;
	SDL_Renderer* renderer;
	SDL_Window* window;
	Position currentPos;
	SDL_Cursor* cpointer;


	std::unordered_map<std::string, Tile> editorTiles;
	int MenuButtonSize = 48;


	Editor(AreaMap* areaMap, SDL_Renderer* render, SDL_Window* win)
	{
		amap = areaMap;
		renderer = render;
		window = win;
		currentPos.set(amap->gridWidth/2, amap->gridHeight/2);
		editorTiles["blank"] = {"Blank", "images/64/blank.png", loadImage("images/64/blank.png"),
								{amap->tileWidth, amap->tileHeight},{0,0,0,0},false};
		editorTiles["hover"] = {"Hover", "images/64/hover.png", loadImage("images/64/hover.png"),
								{amap->tileWidth, amap->tileHeight},{0,0,0,0},false};
		editorTiles["current"] = {"Current", "images/64/current.png", loadImage("images/64/current.png"),
									{amap->tileWidth, amap->tileHeight},{0,0,0,0},false};

		amap->tilesets[0] = newTileset("Tileset1", amap->tileWidth, amap->tileHeight);
		amap->tilesets[0].tiles[1] = newTile("Cave Floor Pass", "images/64/cave-floor-pass.png", amap->tileWidth, amap->tileHeight,false);
		amap->tilesets[0].tiles[2] = newTile("Cave Wall NE", "images/64/cave-wallNE.png", amap->tileWidth, amap->tileWidth,true);
		amap->tilesets[0].tiles[3] = newTile("Cave Wall NW", "images/64/cave-wallNW.png", amap->tileWidth, amap->tileWidth,true);
		amap->tilesets[0].tiles[4] = newTile("Cave Wall SW", "images/64/cave-wallSW.png", amap->tileWidth, amap->tileWidth,true);
		amap->tilesets[0].tiles[5] = newTile("Cave WallCornerN", "images/64/cave-wallcornerN.png", amap->tileWidth, amap->tileWidth,true);
		amap->tilesets[0].tiles[6] = newTile("Cave Block Short", "images/64/cave-block-short.png", amap->tileWidth, amap->tileHeight,false);
		amap->tilesets[0].tiles[7] = newTile("Cave Block Tall", "images/64/cave-block-tall.png", amap->tileWidth, amap->tileWidth,true);
		amap->tilesets[0].tiles[8] = newTile("Cave Peak", "images/64/cave-peak.png", amap->tileWidth, amap->tileWidth,true);
		amap->tilesets[0].tiles[9] = newTile("Dirt", "images/64/dirt.png", amap->tileWidth, amap->tileHeight,false);
		amap->tilesets[0].tiles[10] = newTile("Water", "images/64/water.png", amap->tileWidth, amap->tileHeight,false);

		amap->layers[0].tileset = 0;
		SDL_Surface* psurf = IMG_Load("images/gui/pointer.png");
		cpointer = SDL_CreateColorCursor(psurf, 20, 20);
		SDL_SetCursor(cpointer);

		TTF_Font* fontsmall = TTF_OpenFont("fonts/purisabo.ttf", 12);
		TTF_Font* fontmed = TTF_OpenFont("fonts/purisabo.ttf", 14);
		TTF_Font* fontlarge = TTF_OpenFont("fonts/purisabo.ttf", 16);
	};

	~Editor();
	void renderGrid () {
		//iso_x =  ((x-y) * (tw//2))
		//iso_y =  ((((x+y) * (depth//2)) - (depth * 15)) - depth)
	   SDL_Rect Rect;
	   for (int row = 0; row < amap->gridWidth; row++)
			for (int col = 0; col < amap->gridHeight; col++) {
				int theight, twidth, halfw, halfh, depth;


				theight = amap->tileHeight + amap->zoomY;
				twidth = amap->tileWidth + amap->zoomX;
				halfw = twidth / 2;
				halfh = theight / 2;
				depth = theight;

				int iso_x = (row - col) * halfw;
				int iso_y = ((row+col) * halfh/2);// - depth;// (depth * (amap->gridHeight / 2)) - depth;
				Rect.x = iso_x + amap->offsetX;
				Rect.y = iso_y + amap->offsetY;
				Rect.w = twidth;
				Rect.h = theight;
				Position p = {Rect.x, Rect.y};
				Size s = {Rect.w, Rect.h};
				Area area = Area(p, s);
				area.update();
				if (currentPos.x == row && currentPos.y == col)
					SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
				else
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
				/*SDL_RenderDrawLine(renderer, area.isoLeft.x, area.isoLeft.y, area.isoTop.x, area.isoTop.y);
				SDL_RenderDrawLine(renderer, area.isoTop.x, area.isoTop.y, area.isoRight.x, area.isoRight.y);
				SDL_RenderDrawLine(renderer, area.isoRight.x, area.isoRight.y, area.isoBottom.x, area.isoBottom.y);
				SDL_RenderDrawLine(renderer, area.isoBottom.x, area.isoBottom.y, area.isoLeft.x, area.isoLeft.y);*/
				int tid = amap->layers[0].grid[row][col].tile_id;
				double rot = amap->layers[0].grid[row][col].rotate;
				if ( tid != NULL)
					SDL_RenderCopyEx(renderer, amap->tilesets[0].tiles[tid].texture, NULL, &Rect,
									rot, NULL, SDL_FLIP_NONE);
				else
					SDL_RenderCopy(renderer, editorTiles["blank"].texture, NULL, &Rect);
				if (currentPos.x == row && currentPos.y == col)
					SDL_RenderCopy(renderer, editorTiles["current"].texture, NULL, &Rect);

			} // Col

	};

	SDL_Point clickArea(int screenx, int screeny)
	{
		SDL_Point map;
		map.x = (screenx / (amap->tileWidth/2) + screeny / (amap->tileHeight/2)) /2;
		map.y = (screeny / (amap->tileHeight/2) - screenx / (amap->tileWidth/2)) /2;
		return map;
	}

	void moveCurrent(int mx, int my)
	{
		if (currentPos.x + mx >= 0 && currentPos.x + mx < amap->gridWidth)
			currentPos.x += mx;
		if (currentPos.y + my >= 0 && currentPos.y + my < amap->gridHeight)
			currentPos.y += my;
	}

	void rotateCurrent(int degrees)
	{
		amap->layers[0].grid[currentPos.x][currentPos.y].rotate += degrees;
	}

	void resizeLayerGrid(int w, int h)
	{
		amap->gridWidth += w;
		amap->gridHeight += h;
		amap->layers[0].width += w;
		amap->layers[0].height += h;
		amap->layers[0].updateGrid();
	}

	TileSet newTileset(std::string setName, int tilew, int tileh)
	{
		TileSet ts;
		ts.name = setName;
		ts.tileSize = {tilew, tileh};
		return ts;
	}

	Tile newTile(std::string tileName, std::string tileFilename, int w, int h, bool tall)
	{
		Tile t;
		t.name = tileName;
		t.filename = tileFilename;
		t.size = {w, h};
		t.texture = loadImage(t.filename.c_str());
		t.tall = tall;
		return t;
	}

	void listTileset(int value)
	{
		int iconw = 64;
		int iconh = 64;
		int winw, winh = 0;
		SDL_GetWindowSize(window, &winw, &winh);
		int listx = winw - iconw -2;
		int listy = 100;
		SDL_Rect rect;

		TileSet ts = amap->tilesets[value];
		for (int i = 0; i < ts.tiles.size();i++)
		{
			rect.x = listx;
			rect.y = listy + (i * iconh + 2);
			rect.w = iconw;
			rect.h = iconh;
			SDL_RenderCopy(renderer, ts.tiles[i].texture, NULL, &rect);
		}
	}

	void setCurrentTile(int value)
	{
		amap->layers[0].grid[currentPos.x][currentPos.y].tile_id = value;
	}
	//screen.x = (map.x - map.y) * TILE_WIDTH_HALF;
	//screen.y = (map.x + map.y) * TILE_HEIGHT_HALF;
	SDL_Point maptoScreen(SDL_Point mapcoord, int tw, int th)
	{
		SDL_Point screen;
		screen.x = (mapcoord.x - mapcoord.y) * (tw/2);

		screen.y = (mapcoord.x + mapcoord.y) * (th/2);
		return screen;
	}

	SDL_Point screentoMap(SDL_Point screen, int tw, int th)
	{
		SDL_Point map;
		int twh = tw/2;
		int thh = th/2;
		map.x = (screen.x / twh + screen.y / thh) /2;
		map.y = (screen.y / thh -(screen.x / twh)) /2;
		return map;
	}

	void renderMap()
	{
		for (int row = 0; row < amap->gridWidth;row++)
			for (int col = 0; col < amap->gridHeight;col++)
			{
				int tile_id = amap->layers[0].grid[row][col].tile_id;
				Tile tile = amap->tilesets[0].tiles[tile_id];
				SDL_Point pos = maptoScreen({row,col}, tile.size.w, tile.size.h);
				if (tile.tall)
					pos.x -= tile.size.w; // Tall size tile
				else
					pos.x -= tile.size.w/2; // Normal size tile
				// Offset for 'camera'
				pos.x += amap->offsetX;
				SDL_Rect Rect = {pos.x, pos.y, tile.size.w, tile.size.h};
				SDL_RenderCopy(renderer, tile.texture, NULL, &Rect);


			}

	}

};

}

#endif // _EDITOR_H_
