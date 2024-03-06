#include <iostream>
#include <assert.h>

namespace Constants {
    const int EPSILON = 1e-6;
    const int MAX_VECTOR_COORDINATES = 100;
}

namespace Points {
    enum class Quadrant {
        Q1, Q2, Q3, Q4, Origin, XAxis, YAxis
    };

    struct Point {
        int x = 0;
        int y = 0;
    };

    void readPoint(Point& point) {
        std::cin >> point.x >> point.y;
    }

    void printPoint(const Point& point) {
        std::cout << '(' << point.x << ", " << point.y << ") ";
    }

    Quadrant getPointQuadrant(const Point& point) {
        if (point.x > 0 && point.y > 0) {
            return Quadrant::Q1;
        }
        else if (point.x < 0 && point.y > 0) {
            return Quadrant::Q2;
        }
        else if (point.x < 0 && point.y < 0) {
            return Quadrant::Q3;
        }
        else if (point.x > 0 && point.y < 0) {
            return Quadrant::Q3;
        }
        else if (point.x == 0 && point.y != 0) {
            return Quadrant::YAxis;
        }
        else if (point.x != 0 && point.y == 0) {
            return Quadrant::XAxis;
        }

        return Quadrant::Origin;
    }

    double getDistanceBetweenPoints(const Point& p1, const Point& p2) {
        int dx = p1.x - p2.x;
        int dy = p1.y - p2.y;

        return sqrt(dx * dx + dy * dy);
    }
}

namespace Circles {
    using Points::Point;
    using Points::readPoint;
    using Points::getDistanceBetweenPoints;

    struct Circle {
        Points::Point center;
        double radius;
    };

    void readCircle(Circle& circle) {
        readPoint(circle.center);
        std::cin >> circle.radius;
    }

    bool isPointOnCircleBoundary(const Point& point, const Circle& circle) {
        double distFromCenter = getDistanceBetweenPoints(point, circle.center);
        return abs(distFromCenter - circle.radius) < Constants::EPSILON;
    }

    bool doCirclesIntersect(const Circle& c1, const Circle& c2) {
        double distBetweenCenters = getDistanceBetweenPoints(c1.center, c2.center);
        return distBetweenCenters < (c1.radius + c2.radius);
    }

    bool isCircleInsideOtherCircle(const Circle& inside, const Circle& other) {
        double distBetweenCenters = getDistanceBetweenPoints(inside.center, other.center);
        return distBetweenCenters <= (other.radius - inside.radius);
    }
}

namespace Vectors {
    struct Vector {
        size_t size = 3;
        double coordinates[Constants::MAX_VECTOR_COORDINATES];
    };

    double calculateMagnitude(const Vector& vector) {
        double sumOfSquares = 0.0;
        for (size_t i = 0; i < vector.size; i++) {
            sumOfSquares += vector.coordinates[i] * vector.coordinates[i];
        }

        return sqrt(sumOfSquares);
    }

    double getScalarProduct(const Vector& v1, const Vector& v2) {
        assert(v1.size == v2.size);

        double product = 0.0;
        for (size_t i = 0; i < v1.size; i++) {
            product += v1.coordinates[i] * v2.coordinates[i];
        }

        return product;
    }

    Vector getVectorProduct(const Vector& v1, const Vector& v2) {
        assert(v1.size == 3 && v2.size == 3);

        Vector result;
        result.coordinates[0] = v1.coordinates[1] * v2.coordinates[2] - v1.coordinates[2] * v2.coordinates[1];
        result.coordinates[1] = v1.coordinates[2] * v2.coordinates[0] - v1.coordinates[0] * v2.coordinates[2];
        result.coordinates[2] = v1.coordinates[0] * v2.coordinates[1] - v1.coordinates[1] * v2.coordinates[0];

        return result;
    }
}

namespace Lines {
    using namespace Points;

    struct Line {
        Point start;
        Point end;
    };

    void readLine(Line& line) {
        readPoint(line.start);
        readPoint(line.end);
    }

    void printLine(const Line& line) {
        printPoint(line.start);
        printPoint(line.end);
    }

    double getLineLength(const Line& line) {
        return getDistanceBetweenPoints(line.start, line.end);
    }

    void sortLinesByLength(Line* lines, size_t n) {
        double* lengths = new double[n];
        for (size_t i = 0; i < n; i++) {
            lengths[i] = getLineLength(lines[i]);
        }

        for (size_t i = 0; i < n - 1; i++) {
            size_t minLengthIndex = i;

            for (size_t j = 0; j < n; j++) {
                if (lengths[j] < lengths[minLengthIndex]) {
                    minLengthIndex = j;
                }
            }

            if (minLengthIndex != i) {
                std::swap(lines[i], lines[minLengthIndex]);
                std::swap(lengths[i], lengths[minLengthIndex]);
            }
        }

        delete[] lengths;
    }
}

int main() {
    size_t n;
    std::cin >> n;

    Lines::Line* lines = new Lines::Line[n];
    for (size_t i = 0; i < n; i++) {
        Lines::readLine(lines[i]);
    }

    Lines::sortLinesByLength(lines, n);

    for (size_t i = 0; i < n; i++) {
        Lines::printLine(lines[i]);
        std::cout << std::endl;
    }

    delete[] lines;
}
