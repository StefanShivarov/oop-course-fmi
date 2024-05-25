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

    Shape* clone() const override;

    bool intersectsWith(Shape* shape) override;
    bool intersectsWithRectangle(Rectangle* rectangle) override;
    bool intersectsWithTriangle(Triangle* triangle) override;
    bool intersectsWithCircle(Circle* circle) override;

private:
    double radius;
};
