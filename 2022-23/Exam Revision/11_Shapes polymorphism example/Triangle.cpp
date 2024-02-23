#include "Triangle.h"

Triangle::Triangle(int x1, int y1, int x2, int y2, int x3, int y3) : Shape(3) {

	setPointAt(0, x1, y1);
	setPointAt(1, x2, y2);
	setPointAt(2, x3, y3);

}

double Triangle::getArea() const {

	const Shape::Point& p1 = getPointAtIndex(0);
	const Shape::Point& p2 = getPointAtIndex(1);
	const Shape::Point& p3 = getPointAtIndex(2);

	return abs(p1.x * p2.y + p2.x * p3.y + p3.x * p1.y - p1.y * p2.x - p2.y * p3.x - p3.y * p1.x) / 2.00;
}

double Triangle::getPerimeter() const {

	const Shape::Point& p1 = getPointAtIndex(0);
	const Shape::Point& p2 = getPointAtIndex(1);
	const Shape::Point& p3 = getPointAtIndex(2);

	return p1.getDistanceTo(p2) + p2.getDistanceTo(p3) + p3.getDistanceTo(p1);
}

bool Triangle::isPointInside(int x, int y) const {

	//...insert some formula to determine whether point is inside triangle area or not...
	return false;
}