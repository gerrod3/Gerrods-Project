#include "Collide.h"

bool Collide::collision(Hitbox h1, Hitbox h2) {
	SHAPE s1 = h1.shape;
	bool b;
	switch (s1)
	{
	case SQAURE:
		b = squareCollision(h1, h2);
		break;
	case CIRCLE:
	//	b = circleCollision(h1, h2);
		break;
	case TRIANGLE:
		//b = triangleCollision(h1, h2);
		break;
	default:
		b = false;
		break;

	}
	return b;
}

//first shape is a sqaure
bool Collide::squareCollision(Hitbox h1, Hitbox h2) {
	SHAPE s2 = h2.shape;
	Point tl = { h1.cord.x - (h1.width / 2), h1.cord.y + (h1.height / 2) };
	Point tr = { h1.cord.x + (h1.width / 2), h1.cord.y + (h1.height / 2) };
	Point bl = { h1.cord.x - (h1.width / 2), h1.cord.y - (h1.height / 2) };
	Point br = { h1.cord.x + (h1.width / 2), h1.cord.y - (h1.height / 2) };
	bool b;
	switch (s2)
	{
	case SQAURE:
		b = pointSquareCollision(tl, h2) || pointSquareCollision(tr, h2) || pointSquareCollision(bl, h2) || pointSquareCollision(br, h2);
		break;
		// do rest later lol
	case CIRCLE:
		break;
	case TRIANGLE:
		break;
	default:
		b = false;
		break;
	}
	return b;
}

//will have the other shapeCollision functions here

bool Collide::pointCollision(Point p1, Hitbox h2) {
	SHAPE s2 = h2.shape;
	bool b;
	switch (s2)
	{
	case SQAURE:
		b = pointSquareCollision(p1, h2);
		break;
	case CIRCLE:
	//	b = pointCircleCollision(p1, h2);
		break;
	case TRIANGLE:
		//b = pointTriangleCollision(p1, h2);
		break;
	default:
		b = false;
		break;
	}
	return b;
}

bool Collide::pointSquareCollision(Point p1, Hitbox h2) {
	float left = h2.cord.x - (h2.width / 2);
	float right = h2.cord.x + (h2.width / 2);
	float top = h2.cord.y + (h2.height / 2);
	float bot = h2.cord.y - (h2.height / 2);
	float x = p1.x;
	float y = p1.y;


	if ((x >= left && x <= right) && (y <= top && y >= bot)) {
		return true;
	}
	else {
		return false;
	}

}