#pragma once
#include <iostream>

class Triangle;
class Rectangle;
class Circle;

class Shape
{
public:
    explicit Shape(size_t pointsCount);

    Shape(const Shape& other);
    Shape(Shape&& other) noexcept;

    Shape& operator=(const Shape& other);
    Shape& operator=(Shape&& other) noexcept;

    virtual ~Shape();

    void setPoint(size_t index, int x, int y);

    virtual double getArea() const = 0;
    virtual double getPerimeter() const;
    virtual bool isPointInside(int x, int y) const = 0;

    virtual Shape* clone() const = 0;

    // visitor pattern
    virtual bool intersectsWith(Shape* shape) = 0;
    virtual bool intersectsWithRectangle(Rectangle* rectangle) = 0;
    virtual bool intersectsWithTriangle(Triangle* triangle) = 0;
    virtual bool intersectsWithCircle(Circle* circle) = 0;

protected:
    struct Point {
        int x;
        int y;

        Point() : x(0), y(0) {}
        Point(int x, int y) : x(x), y(y) {}

        double getDistanceTo(const Point& other) const 
        {
            int dx = x - other.x;
            int dy = y - other.y;
            return sqrt(dx * dx + dy * dy);
        }
    };
    
    const Point& getPointAtIndex(size_t index) const;
private:
    Point* points;
    size_t pointsCount;

    void free();
    void copyFrom(const Shape& other);
    void moveFrom(Shape&& other) noexcept;
};
