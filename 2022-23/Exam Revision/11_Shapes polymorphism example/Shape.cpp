#include "Shape.h"

void Shape::free(){
	delete[] points;
}

void Shape::copyFrom(const Shape& other) {

	pointsAmount = other.pointsAmount;
	points = new Point[pointsAmount];
	for (size_t i = 0; i < pointsAmount; i++) {
		points[i] = other.points[i];
	}
}

void Shape::move(Shape&& other) {

	pointsAmount = other.pointsAmount;
	points = other.points;
	other.points = nullptr;
	other.pointsAmount = 0;
}

Shape::Shape(size_t pointsAmount) : pointsAmount(pointsAmount) {

	points = new Point[pointsAmount];
}

Shape::Shape(const Shape& other) {
	copyFrom(other);
}

Shape& Shape::operator=(const Shape& other) {

	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Shape::Shape(Shape&& other) {
	move(std::move(other));
}

Shape& Shape::operator=(Shape&& other) {

	if (this != &other) {
		free();
		move(std::move(other));
	}
	return *this;
}

Shape::~Shape() {
	free();
}

void Shape::setPointAt(size_t index, int x, int y) {

	if (index >= pointsAmount) {
		throw std::logic_error("Error! Invalid point index!");
	}
	points[index] = Point(x, y);
}

const Shape::Point& Shape::getPointAtIndex(size_t index) const {

	if (index >= pointsAmount) {
		throw std::logic_error("Error! Invalid point index!");
	}
	return points[index];
}