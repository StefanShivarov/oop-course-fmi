#pragma once
#include <iostream>

class Shape
{

protected:

	struct Point {

		int x;
		int y;

		Point() : x(0), y(0) {}
		Point(int x, int y) : x(x), y(y) {}

		double getDistanceTo(const Point& other) const {
			return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
		}
	};

	const Point& getPointAtIndex(size_t index) const;

private:

	Point* points;
	size_t pointsAmount;

	void free();
	void copyFrom(const Shape& other);
	void move(Shape&& other);

public:

	Shape(size_t pointsAmount);
	Shape(const Shape& other);
	Shape& operator=(const Shape& other);
	Shape(Shape&& other) noexcept;
	Shape& operator=(Shape&& other) noexcept;
	virtual ~Shape();

	void setPointAt(size_t index, int x, int y);

	virtual double getPerimeter() const = 0;
	virtual double getArea() const = 0;
	virtual bool isPointInside(int x, int y) const = 0;


};