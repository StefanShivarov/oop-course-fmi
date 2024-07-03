#pragma once
class Size
{
public:
    Size() = default;
    Size(size_t width, size_t height);

    size_t getWidth() const;
    size_t getHeight() const;
private:
    size_t width = 10;
    size_t height = 10;
};

