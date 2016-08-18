#ifndef _COMMON_H
#define _COMMON_H
#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace iso
{
// Forward Declarations
struct Cfg;

// Typedefs and Aliases
typedef struct Cfg AppCfg;

// Cfg Constants
static const int WINDOWWIDTH = 1300;
static const int WINDOWHEIGHT = 700;
static const int WINDOWX = 100;
static const int WINDOWY = 25;
static const int WINDOWFLAGS = SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE|SDL_WINDOW_OPENGL;
static const char* TITLE = "IsoEditor Alpha .5	z";
static const int RENDFLAGS = SDL_RENDERER_ACCELERATED;
static const int INITFLAGS = SDL_INIT_EVERYTHING;
static const int INITIMGFLAGS = IMG_INIT_PNG|IMG_INIT_PNG;

// ISO Declarations
//static Cfg cfg;

// Objects, Functions

// AppCfg to control the Window Utilities seperate from Maps, Tiles, Layers,etc.
struct Cfg
{
	SDL_Window* screen;
	SDL_Renderer* renderer;
	// initialize Video, IMG, Window, Renderer
	void init()
	{
		if (SDL_Init(SDL_INIT_VIDEO) == -1)
			std::cout << "Unable to init SDL video: "<< SDL_GetError() << std::endl;
		if (IMG_Init(IMG_INIT_PNG) == -1)
			std::cout << "IMG_init Puked: " << IMG_GetError() << std::endl;
		if (TTF_Init() == -1)
			std::cout << "TTF_Init Puked: " << TTF_GetError() << std::endl;
		screen = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  WINDOWWIDTH, WINDOWHEIGHT, WINDOWFLAGS);
		renderer = SDL_CreateRenderer(screen, -1, RENDFLAGS);
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
		SDL_RenderSetLogicalSize(renderer, WINDOWWIDTH, WINDOWHEIGHT);
		if ( NULL == screen)
			std::cout << "Unable to create window: "<< SDL_GetError() << std::endl;
		if ( NULL == renderer )
			std::cout << "Unable to create renderer: "<< SDL_GetError() << std::endl;
	}
	// Set RenderColor using our predefined colors
	void setRenderColor (const SDL_Color *color, Uint8 alpha=255)
	{
		SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, alpha);
	}

} cfg;

// Objects, Functions, etc unrelated to the underlying apps

// Load image into a Texture
extern SDL_Texture* loadImage(const char* name)
{
    SDL_Surface* bitmap = NULL;
    bitmap = IMG_Load(name);
    if ( NULL == bitmap )
    {
        std::cout << "Unable to load bitmap: "<< SDL_GetError() << std::endl;
        return NULL;
    }
    SDL_Texture* texture = NULL;
    texture = SDL_CreateTextureFromSurface(cfg.renderer, bitmap);
    SDL_FreeSurface(bitmap);
	if (NULL == texture)
	{
		std::cout << "Texture is NULL!" << SDL_GetError() << std::endl;
		return NULL;
	}
	return texture;
}

//Get a Rect for your Texture
extern SDL_Rect getRect(SDL_Texture* src, int x = 0, int y = 0) {
	SDL_Rect rect {};
	SDL_QueryTexture(src, NULL, NULL, &rect.w, &rect.h);
	rect.x = x;
	rect.y = y;
	return rect;
}

} // ns iso


// Color presets

const SDL_Color RED = {255, 0, 0, 255};
const SDL_Color GREEN = { 0, 128, 0, 255};
const SDL_Color BLUE = { 0, 0, 255, 255};
const SDL_Color YELLOW = {255, 255, 0, 255};
const SDL_Color CYAN = { 0, 255, 255, 255};
const SDL_Color MAGENTA = {255, 0, 255, 255};
const SDL_Color BLACK = { 0, 0, 0, 255};
const SDL_Color GREY = {128, 128, 128, 255};
const SDL_Color GRAY = {128, 128, 128, 255};
const SDL_Color WHITE = {255, 255, 255, 255};
// Fancier colors
const SDL_Color ALICEBLUE = {240, 248, 255, 255};
const SDL_Color ANTIQUEWHITE = {250, 235, 215, 255};
const SDL_Color AQUA = { 0, 255, 255, 255};
const SDL_Color AQUAMARINE = {127, 255, 212, 255};
const SDL_Color AZURE = {240, 255, 255, 255};
const SDL_Color BEIGE = {245, 245, 220, 255};
const SDL_Color BISQUE = {255, 228, 196, 255};
const SDL_Color BLANCHEDALMOND = {255, 235, 205, 255};
const SDL_Color BLUEVIOLET = {138, 43, 226, 255};
const SDL_Color BROWN = {165, 42, 42, 255};
const SDL_Color BURLYWOOD = {222, 184, 135, 255};
const SDL_Color CADETBLUE = { 95, 158, 160, 255};
const SDL_Color CHARTREUSE = {127, 255, 0, 255};
const SDL_Color CHOCOLATE = {210, 105, 30, 255};
const SDL_Color CORAL = {255, 127, 80, 255};
const SDL_Color CORNFLOWERBLUE = {100, 149, 237, 255};
const SDL_Color CORNSILK = {255, 248, 220, 255};
const SDL_Color CRIMSON = {220, 20, 60, 255};
const SDL_Color DARKBLUE = { 0, 0, 139, 255};
const SDL_Color DARKCYAN = { 0, 139, 139, 255};
const SDL_Color DARKGOLDENROD = {184, 134, 11, 255};
const SDL_Color DARKGRAY = {169, 169, 169, 255};
const SDL_Color DARKGREEN = { 0, 100, 0, 255};
const SDL_Color DARKGREY = {169, 169, 169, 255};
const SDL_Color DARKKHAKI = {189, 183, 107, 255};
const SDL_Color DARKMAGENTA = {139, 0, 139, 255};
const SDL_Color DARKOLIVEGREEN = { 85, 107, 47, 255};
const SDL_Color DARKORANGE = {255, 140, 0, 255};
const SDL_Color DARKORCHID = {153, 50, 204, 255};
const SDL_Color DARKRED = {139, 0, 0, 255};
const SDL_Color DARKSALMON = {233, 150, 122, 255};
const SDL_Color DARKSEAGREEN = {143, 188, 143, 255};
const SDL_Color DARKSLATEBLUE = { 72, 61, 139, 255};
const SDL_Color DARKSLATEGRAY = { 47, 79, 79, 255};
const SDL_Color DARKSLATEGREY = { 47, 79, 79, 255};
const SDL_Color DARKTURQUOISE = { 0, 206, 209, 255};
const SDL_Color DARKVIOLET = {148, 0, 211, 255};
const SDL_Color DEEPPINK = {255, 20, 147, 255};
const SDL_Color DEEPSKYBLUE = { 0, 191, 255, 255};
const SDL_Color DIMGRAY = {105, 105, 105, 255};
const SDL_Color DIMGREY = {105, 105, 105, 255};
const SDL_Color DODGERBLUE = { 30, 144, 255, 255};
const SDL_Color FIREBRICK = {178, 34, 34, 255};
const SDL_Color FLORALWHITE = {255, 250, 240, 255};
const SDL_Color FORESTGREEN = { 34, 139, 34, 255};
const SDL_Color FUCHSIA = {255, 0, 255, 255};
const SDL_Color GAINSBORO = {220, 220, 220, 255};
const SDL_Color GHOSTWHITE = {248, 248, 255, 255};
const SDL_Color GOLD = {255, 215, 0, 255};
const SDL_Color GOLDENROD = {218, 165, 32, 255};
const SDL_Color GREENYELLOW = {173, 255, 47, 255};
const SDL_Color HONEYDEW = {240, 255, 240, 255};
const SDL_Color HOTPINK = {255, 105, 180, 255};
const SDL_Color INDIANRED = {205, 92, 92, 255};
const SDL_Color INDIGO = { 75, 0, 130, 255};
const SDL_Color IVORY = {255, 255, 240, 255};
const SDL_Color KHAKI = {240, 230, 140, 255};
const SDL_Color LAVENDER = {230, 230, 250, 255};
const SDL_Color LAVENDERBLUSH = {255, 240, 245, 255};
const SDL_Color LAWNGREEN = {124, 252, 0, 255};
const SDL_Color LEMONCHIFFON = {255, 250, 205, 255};
const SDL_Color LIGHTBLUE = {173, 216, 230, 255};
const SDL_Color LIGHTCORAL = {240, 128, 128, 255};
const SDL_Color LIGHTCYAN = {224, 255, 255, 255};
const SDL_Color LIGHTGOLDENRODYELLOW = {250, 250, 210, 255};
const SDL_Color LIGHTGRAY = {211, 211, 211, 255};
const SDL_Color LIGHTGREEN = {144, 238, 144, 255};
const SDL_Color LIGHTGREY = {211, 211, 211, 255};
const SDL_Color LIGHTPINK = {255, 182, 193, 255};
const SDL_Color LIGHTSALMON = {255, 160, 122, 255};
const SDL_Color LIGHTSEAGREEN = { 32, 178, 170, 255};
const SDL_Color LIGHTSKYBLUE = {135, 206, 250, 255};
const SDL_Color LIGHTSLATEGRAY = {119, 136, 153, 255};
const SDL_Color LIGHTSLATEGREY = {119, 136, 153, 255};
const SDL_Color LIGHTSTEELBLUE = {176, 196, 222, 255};
const SDL_Color LIGHTYELLOW = {255, 255, 224, 255};
const SDL_Color LIME = { 0, 255, 0, 255};
const SDL_Color LIMEGREEN = { 50, 205, 50, 255};
const SDL_Color LINEN = {250, 240, 230, 255};
const SDL_Color MAROON = {128, 0, 0, 255};
const SDL_Color MEDIUMAQUAMARINE = {102, 205, 170, 255};
const SDL_Color MEDIUMBLUE = { 0, 0, 205, 255};
const SDL_Color MEDIUMORCHID = {186, 85, 211, 255};
const SDL_Color MEDIUMPURPLE = {147, 112, 219, 255};
const SDL_Color MEDIUMSEAGREEN = { 60, 179, 113, 255};
const SDL_Color MEDIUMSLATEBLUE = {123, 104, 238, 255};
const SDL_Color MEDIUMSPRINGGREEN = { 0, 250, 154, 255};
const SDL_Color MEDIUMTURQUOISE = { 72, 209, 204, 255};
const SDL_Color MEDIUMVIOLETRED = {199, 21, 133, 255};
const SDL_Color MIDNIGHTBLUE = { 25, 25, 112, 255};
const SDL_Color MINTCREAM = {245, 255, 250, 255};
const SDL_Color MISTYROSE = {255, 228, 225, 255};
const SDL_Color MOCCASIN = {255, 228, 181, 255};
const SDL_Color NAVAJOWHITE = {255, 222, 173, 255};
const SDL_Color NAVY = { 0, 0, 128, 255};
const SDL_Color OLDLACE = {253, 245, 230, 255};
const SDL_Color OLIVE = {128, 128, 0, 255};
const SDL_Color OLIVEDRAB = {107, 142, 35, 255};
const SDL_Color ORANGE = {255, 165, 0, 255};
const SDL_Color ORANGERED = {255, 69, 0, 255};
const SDL_Color ORCHID = {218, 112, 214, 255};
const SDL_Color PALEGOLDENROD = {238, 232, 170, 255};
const SDL_Color PALEGREEN = {152, 251, 152, 255};
const SDL_Color PALETURQUOISE = {175, 238, 238, 255};
const SDL_Color PALEVIOLETRED = {219, 112, 147, 255};
const SDL_Color PAPAYAWHIP = {255, 239, 213, 255};
const SDL_Color PEACHPUFF = {255, 218, 185, 255};
const SDL_Color PERU = {205, 133, 63, 255};
const SDL_Color PINK = {255, 192, 203, 255};
const SDL_Color PLUM = {221, 160, 221, 255};
const SDL_Color POWDERBLUE = {176, 224, 230, 255};
const SDL_Color PURPLE = {128, 0, 128, 255};
const SDL_Color ROSYBROWN = {188, 143, 143, 255};
const SDL_Color ROYALBLUE = { 65, 105, 225, 255};
const SDL_Color SADDLEBROWN = {139, 69, 19, 255};
const SDL_Color SALMON = {250, 128, 114, 255};
const SDL_Color SANDYBROWN = {244, 164, 96, 255};
const SDL_Color SEAGREEN = { 46, 139, 87, 255};
const SDL_Color SEASHELL = {255, 245, 238, 255};
const SDL_Color SIENNA = {160, 82, 45, 255};
const SDL_Color SILVER = {192, 192, 192, 255};
const SDL_Color SKYBLUE = {135, 206, 235, 255};
const SDL_Color SLATEBLUE = {106, 90, 205, 255};
const SDL_Color SLATEGRAY = {112, 128, 144, 255};
const SDL_Color SLATEGREY = {112, 128, 144, 255};
const SDL_Color SNOW = {255, 250, 250, 255};
const SDL_Color SPRINGGREEN = { 0, 255, 127, 255};
const SDL_Color STEELBLUE = { 70, 130, 180, 255};
const SDL_Color TAN = {210, 180, 140, 255};
const SDL_Color TEAL = { 0, 128, 128, 255};
const SDL_Color THISTLE = {216, 191, 216, 255};
const SDL_Color TOMATO = {255, 99, 71, 255};
const SDL_Color TURQUOISE = { 64, 224, 208, 255};
const SDL_Color VIOLET = {238, 130, 238, 255};
const SDL_Color WHEAT = {245, 222, 179, 255};
const SDL_Color WHITESMOKE = {245, 245, 245, 255};
const SDL_Color YELLOWGREEN = {154, 205, 50, 255};

#endif