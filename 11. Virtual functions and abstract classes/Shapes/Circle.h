#pragma once
#include "Shape.h"

class Circle : public Shape
{
public:
    Circle(int x, int y, double radius);

    double getRadius() const;

    double getArea() const override;
    double getPerimeter() const override;
    bool isPointInside(int x, int y) const override;

private:
    double radius;
};
