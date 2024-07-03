#pragma once
#include "Shape.h"

class ShapeCollection
{
public:
    ShapeCollection();

    ShapeCollection(const ShapeCollection& other);
    ShapeCollection(ShapeCollection&& other) noexcept;

    ShapeCollection& operator=(const ShapeCollection& other);
    ShapeCollection& operator=(ShapeCollection&& other) noexcept;

    ~ShapeCollection() noexcept;

    void addShape(Shape* shape);
    void addShape(const Shape& shape);

    double getAreaAtIndex(size_t index) const;
    double getPerimeterAtIndex(size_t index) const;
    double isPointInsideAtIndex(size_t index, int x, int y) const;

    const Shape* operator[](size_t index) const;
    unsigned getSize() const;

private:
    Shape** shapes;
    size_t shapesCount;
    size_t shapesCapacity;

    void resize(size_t newCapacity);
    void free();
    void copyFrom(const ShapeCollection& other);
    void moveFrom(ShapeCollection&& other) noexcept;
};

