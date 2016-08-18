#ifndef _LAYOUT_H
#define _LAYOUT_H
#include <vector>
#include <unordered_map>
#include <SDL2/SDL.h>


namespace iso
{

struct Position
{
	int x;
	int y;

	void set(int dx, int dy)
	{
		x = dx;
		y = dy;
	};

	void adjust(int dx, int dy)
	{
		x += dx;
		y += dy;
	};

	int get() { return x,y;};
};

struct Size
{
	int w;
	int h;

};

struct Area
{
	Position position;
	Size size;
	Position tl, tr, bl, br;
	Position isoTop, isoBottom, isoLeft, isoRight;

	Area()
	{
		position = {0,0};
		size = {0,0};
		update();
	};
	Area(Position p, Size s)
	{
		position = p;
		size = s;
		update();
	};
	void update()
	{
		bl.set(position.x, position.y);
		br.set(position.x+size.w, position.y);
		tl.set(position.x, position.y+size.h);
		tr.set(position.x+size.w, position.y+size.h);
		isoTop.set(tl.x+size.w/2, tl.y);
		isoBottom.set(bl.x+size.w/2, bl.y);
		isoLeft.set(bl.x, bl.y+size.h/2);
		isoRight.set(br.x, br.y+size.h/2);
	}
};

struct Tile
{
	std::string name;
	std::string filename;
	SDL_Texture* texture;
	Size size;
	SDL_Rect rect;
	bool tall;
};

struct TileSet
{
	std::string name;
	Size tileSize;
	int numTiles = 0;
	std::unordered_map<int,Tile> tiles;
};

struct AreaTile
{
	Position pos;
	Area area;
	int tile_id;
	int rotate;
};

struct Layer
{
	const char* name;
	int width;
	int height;
	int twidth;
	int theight;
	int tileset;
	std::vector<std::vector<AreaTile>> grid;
	Layer(){
		name = "Layer";
		width = 8;
		height = 8;
	}
	Layer(const char* n, int w, int h, int tw, int th)
	{
		name = n;
		width = w;
		height = h;
		twidth = tw;
		theight = th;
		updateGrid();

	}
	void updateGrid()
	{
		grid.resize(width);
		for (int row = 0; row < width;row++)
			grid[row].resize(height);
	}
};

struct AreaMap
{
	const char* name;
	int tileWidth;
	int tileHeight;
	int gridWidth;
	int gridHeight;
	int zoomX;
	int zoomY;
	int offsetX;
	int offsetY;

	std::vector<Layer> layers;
	std::unordered_map<int,TileSet> tilesets;
	AreaMap(const char* n, int tw, int th, int gw, int gh)
	{
		name = n;
		tileWidth = tw;
		tileHeight = th;
		gridWidth = gw;
		gridHeight = gh;
		layers.resize(1);
		Layer *l = new Layer("Layer1", gridWidth, gridHeight, tileWidth, tileHeight);
		layers[0] = *l;
		zoomX = 0;
		zoomY = 0;
		offsetX = 0;
		offsetY = 0;

	}



};

class Layout
{
public:
	Layout();
	~Layout();

};

}

#endif // _LAYOUT_H
