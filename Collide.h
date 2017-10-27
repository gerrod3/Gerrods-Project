#pragma once
#include "Variables.h"

class Collide {

	Collide(){}
public:

	static bool collision(Hitbox h1, Hitbox h2);
	static bool squareCollision(Hitbox h1, Hitbox h2);
	//static bool circleCollision(Hitbox h1, Hitbox h2);
	//static bool triangleCollision(Hitbox h1, Hitbox h2);

	static bool pointCollision(Point p1, Hitbox h2);
	static bool pointSquareCollision(Point p1, Hitbox h2);
	//static bool pointCircleCollision(Point p1, Hitbox h2);
	//static bool pointTriangleCollision(Point p1, Hitbox h2);

	

};


