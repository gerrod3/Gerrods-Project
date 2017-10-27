#pragma once
#include <vector>

struct Point{
	float x;
	float y;
};


enum SHAPE {
	SQAURE,
	CIRCLE,
	TRIANGLE
};

enum COLOR {
	BLUE,
	RED,
	GREEN,
	BLACK,
	WHITE,
	YELLOW,
	ORANGE,
	PURPLE,
	BROWN,
	GREY
};

//center based hitbox, and right side up based cords
struct Hitbox {
	Point cord;
	float width;
	float height;
	SHAPE shape;
};
//Top-left based hitbox/cord
struct TLOHitbox {
	float left;
	float top;
	float right;
	float bot;
};

#define hbZero Hitbox{{0,0},0,0,SHAPE::SQAURE}
#define hbtlZero TLOHitbox{0,0,0,0}

struct UI_INFO {
	Hitbox HB;
	COLOR color;
	int id;
	int parent;
	std::vector<int> childs;
	static int idCounter;
	bool clickable;
	bool triggered;
	bool dragable;
	//ui's that are visible will be drawn
	bool visible;
	//any ui that is alive will be checked for when updating
	bool alive;
	
	wchar_t* uiName;
	TLOHitbox spriteHB;

};

enum INPUTACTION {
	PRIMARY_CLICK,
	SECONDARY_CLICK,
	PRIMARY_RELEASE,
	SECONDARY_RELEASE,
	KEY_DOWN,
	KEY_RELEASE,
	MOUSE_MOVE
};

struct IA {
	INPUTACTION action;
	int key;
};
