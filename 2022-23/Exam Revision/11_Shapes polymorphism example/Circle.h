#pragma once
#include "Shape.h"


class Circle : public Shape
{

	double radius;

public:

	Circle(int x, int y, double radius);

	void setRadius(double radius);

	double getPerimeter() const override;
	double getArea() const override;
	bool isPointInside(int x, int y) const override;

};

