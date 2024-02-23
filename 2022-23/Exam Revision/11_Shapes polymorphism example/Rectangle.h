#pragma once
#include "Shape.h"

class Rectangle : public Shape
{

public:

	Rectangle(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);

	double getPerimeter() const override;
	double getArea() const override;
	bool isPointInside(int x, int y) const override;
};