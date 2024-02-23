#include "Rectangle.h"

Rectangle::Rectangle(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) : Shape(4) {

	setPointAt(0, x1, y1);
	setPointAt(1, x2, y2);
	setPointAt(2, x3, y3);
	setPointAt(3, x4, y4);
}

double Rectangle::getArea() const {

	const Shape::Point& pA = getPointAtIndex(0);
	const Shape::Point& pB = getPointAtIndex(1);
	const Shape::Point& pD = getPointAtIndex(3);

	return pA.getDistanceTo(pB) * pA.getDistanceTo(pD);
}

double Rectangle::getPerimeter() const {

	const Shape::Point& pA = getPointAtIndex(0);
	const Shape::Point& pB = getPointAtIndex(1);
	const Shape::Point& pD = getPointAtIndex(3);

	return 2 * (pA.getDistanceTo(pB) + pA.getDistanceTo(pD));
}

bool Rectangle::isPointInside(int x, int y) const {

	Shape::Point p(x, y);
	return p.x >= getPointAtIndex(0).x && p.y >= getPointAtIndex(1).x &&
		p.y <= getPointAtIndex(0).y && p.y >= getPointAtIndex(2).y;
}