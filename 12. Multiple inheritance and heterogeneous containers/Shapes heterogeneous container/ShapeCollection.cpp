#include "ShapeCollection.h"

ShapeCollection::ShapeCollection() : shapesCapacity(8), shapesCount(0)
{
    shapes = new Shape * [shapesCapacity] {nullptr};
}

ShapeCollection::ShapeCollection(const ShapeCollection& other)
{
    copyFrom(other);
}

ShapeCollection::ShapeCollection(ShapeCollection&& other) noexcept
{
    moveFrom(std::move(other));
}

ShapeCollection& ShapeCollection::operator=(const ShapeCollection& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

ShapeCollection& ShapeCollection::operator=(ShapeCollection&& other) noexcept
{
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

ShapeCollection::~ShapeCollection() noexcept
{
    free();
}

void ShapeCollection::addShape(Shape* shape)
{
    if (shapesCount == shapesCapacity) {
        resize(shapesCapacity * 2);
    }
    shapes[shapesCount++] = shape;
}

void ShapeCollection::addShape(const Shape& shape)
{
    Shape* shapeToAdd = shape.clone();
    addShape(shapeToAdd);
}

double ShapeCollection::getAreaAtIndex(size_t index) const
{
    return shapes[index]->getArea();
}

double ShapeCollection::getPerimeterAtIndex(size_t index) const
{
    return shapes[index]->getPerimeter();
}

double ShapeCollection::isPointInsideAtIndex(size_t index, int x, int y) const
{
    return shapes[index]->isPointInside(x, y);
}

const Shape* ShapeCollection::operator[](size_t index) const
{
    return shapes[index];
}

unsigned ShapeCollection::getSize() const
{
    return shapesCount;
}

void ShapeCollection::resize(size_t newCapacity)
{
    Shape** resizedShapes = new Shape * [newCapacity];
    for (size_t i = 0; i < shapesCount; i++) {
        resizedShapes[i] = shapes[i];
    }
    delete[] shapes;
    shapes = resizedShapes;
    shapesCapacity = newCapacity;
}

void ShapeCollection::free()
{
    for (size_t i = 0; i < shapesCount; i++) {
        delete shapes[i];
    }
    delete[] shapes;
    shapes = nullptr;
    shapesCount = shapesCapacity = 0;
}

void ShapeCollection::copyFrom(const ShapeCollection& other)
{
    shapes = new Shape * [other.shapesCapacity];
    for (size_t i = 0; i < other.shapesCount; i++) {
        shapes[i] = other.shapes[i]->clone();
    }
    shapesCount = other.shapesCount;
    shapesCapacity = other.shapesCapacity;
}

void ShapeCollection::moveFrom(ShapeCollection&& other) noexcept
{
    shapes = other.shapes;
    other.shapes = nullptr;

    shapesCount = other.shapesCount;
    other.shapesCount = 0;

    shapesCapacity = other.shapesCapacity;
    other.shapesCapacity = 0;
}
