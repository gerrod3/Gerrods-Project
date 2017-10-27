#pragma once
#include "Variables.h"

class Ui {
	

	UI_INFO* info;
public:

	Ui(wchar_t* uiName,float x, float y, float wid, float hig, SHAPE shape, COLOR color, int id);
	Ui(wchar_t* uiName, Hitbox uiHB, TLOHitbox spriteHB,int id);
		
	void changeHB(Hitbox newHB) {info->HB = newHB;}
	void setClickable(bool b) { info->clickable = b; }
	void setTriggered(bool b) { info->triggered = b; }
	void setDragable(bool b) { info->dragable = b; }
	void setAlive(bool b) { info->alive = b; }
	void setVisible(bool b) { info->visible = b; }
	void setParent(int i) { info->parent = i; }
	void addChild(int i) { info->childs.push_back(i); }
	void setChilds(std::vector<int> *c) { info->childs = *c; }
	bool checkedTriggered() { return info->triggered; }
	bool checkClickable() { return info->clickable; }
	bool checkDragable() { return info->dragable; }
	bool checkAlive() { return info->alive; }
	bool checkVisible() { return info->visible; }
	
	Hitbox getHitbox() { return info->HB; }
	TLOHitbox getSpriteHitbox() { return info->spriteHB; }
	COLOR getColor() { return info->color; }
	SHAPE getShape() { return info->HB.shape; }
	int getID() {	return info->id;	}
	int getParent() { return info->parent; }
	bool hasParent() { if (info->parent == -1) return false; else return true; }
	bool hasChild() { if (info->childs.size() > 0) return true; else return false; }
	std::vector<int>* getChilds() { return &info->childs; }
	void changeSpriteHB(TLOHitbox newHB) { info->spriteHB = newHB; }


};