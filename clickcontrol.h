#ifndef _CLICKCONTROL_H_
#define _CLICKCONTROL_H_
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace iso
{
extern SDL_Texture* loadImage(const char* name);
//extern SDL_Rect getRect(SDL_Texture* src, int x = 0, int y = 0);

struct Action
{
	std::string name;
	std::string desc;
	bool active;

};

struct MenuItem
{
	Action action;
	SDL_Texture* button;
	SDL_Rect rect;
	bool show;
	bool pressed;

};
enum Direction { HORIZONTAL, VERTICAL };
struct MenuBar
{
	std::string name;
	SDL_Rect rect;
	int margin = 2;
	Direction direction;
	std::vector<MenuItem> menuItems;
	bool show = true;
};
struct SettingsItem
{
	std::string name;
	std::string value;
	MenuItem menuItem;
};

struct SettingsPanel
{
	std::string heading;
	SDL_Rect headingRect;
	SDL_Texture* panel;
	SDL_Rect panelRect;
	const char* bgFilename;
	const char* fgFilename;
	SDL_Texture* bgImage;
	SDL_Texture* fgImage;
	SDL_Texture* itemButton;
	TTF_Font* headingFont;
	TTF_Font* itemFont;
	SDL_Color headingColor;
	SDL_Color itemColor;
	std::vector<SettingsItem> items;
	bool show;
	bool minimized;

};
class ClickControl
{
	public:
	SDL_Renderer* renderer;
	Editor* editor;
	SDL_Window* window;
	static const int MenuButtonSize = 48;
	static const int MenuBarSize = 64;
	std::vector<MenuItem> controlRegistery;
	std::vector<Action> activeActions;
	std::vector<MenuBar> menuBars;

	ClickControl(SDL_Renderer* rend, Editor* ed, SDL_Window* win);
	~ClickControl();
	SDL_Texture* MenuButton(const char* bgimage, const char* fgimage, int w=MenuBarSize, int h=MenuBarSize);
	void renderMenuBar();
	void add(MenuItem menuItem);
	void remove(std::string name);
	void doRender();
	void doInput(int x, int y);
	void updateActions();
	bool doAction(std::string name);
	void toggle(bool value);
	void textButton(TTF_Font* font, std::string text, SDL_Texture* button);
	SettingsPanel* createSettingsPanel(std::string head, const char* bgfile, const char* fgfile, int x, int y, int w, int h);

};

}

#endif // _CLICKCONTROL_H_
