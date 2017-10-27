#include "Ui.h"

 Ui::Ui(wchar_t* uiName,float x, float y, float wid, float hig, SHAPE shap, COLOR col, int i)
{
	info->uiName=uiName;
	info->HB.cord.x = x;
	info->HB.cord.y = y;
	info->HB.width = wid;
	info->HB.height = hig;
	info->HB.shape = shap;
	info->color = col;
	info->id = i;
	

}

 Ui::Ui(wchar_t* uiName, Hitbox uiHB, TLOHitbox sHB, int i) {
	 info = new UI_INFO;
	 info->uiName= uiName;
	 
	 info->HB = uiHB;
	 info->spriteHB = sHB;
	 info->id = i;
	 info->childs ={};
	 info->parent = -1;
	 info->alive = true;
	 info->visible = true;
	 info->dragable = false;
	 info->clickable = false;
	 info->triggered = false;
 }