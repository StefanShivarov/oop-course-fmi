#include "Circle.h"

const double PI = 3.1415;

Circle::Circle(int x, int y, double radius) : Shape(1) {

	setPointAt(0, x, y);
	setRadius(radius);
}

void Circle::setRadius(double radius) {
	
	if (radius < 0) {
		throw std::logic_error("Error! Invalid radius!");
	}
	this->radius = radius;
}

double Circle::getPerimeter() const {
	return 2 * PI * radius;
}

double Circle::getArea() const {
	return PI * radius * radius;
}

bool Circle::isPointInside(int x, int y) const {
	
	Shape::Point point(x, y);
	return point.getDistanceTo(getPointAtIndex(0)) <= radius;
}