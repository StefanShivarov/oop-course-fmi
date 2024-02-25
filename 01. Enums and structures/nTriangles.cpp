#include <iostream>

namespace Points {
    struct Point {
        int x = 0;
        int y = 0;
    };

    void readPoint(Point& point) {
        std::cin >> point.x >> point.y;
    }

    double getDistanceBetweenPoints(const Point& p1, const Point& p2) {
        int dx = p1.x - p2.x;
        int dy = p1.y - p2.y;

        return sqrt(dx * dx + dy * dy);
    }

    void printPoint(const Point& point) {
        std::cout << '(' << point.x << ", " << point.y << ") ";
    }
}

namespace Triangles {
    using namespace Points;

    struct Triangle {
        Point p1;
        Point p2;
        Point p3;
    };

    void readTriangle(Triangle& triangle) {
        readPoint(triangle.p1);
        readPoint(triangle.p2);
        readPoint(triangle.p3);
    }

    double getTriangleArea(const Triangle& triangle) {
        double a = getDistanceBetweenPoints(triangle.p1, triangle.p2);
        double b = getDistanceBetweenPoints(triangle.p1, triangle.p3);
        double c = getDistanceBetweenPoints(triangle.p2, triangle.p3);
        double halfPer = (a + b + c) / 2;

        return sqrt(halfPer * (halfPer - a) * (halfPer - b) * (halfPer - c));
    }

    void sortTrianglesByArea(Triangle* triangles, size_t n) {
        double* areas = new double[n];
        for (size_t i = 0; i < n; i++) {
            areas[i] = getTriangleArea(triangles[i]);
        }

        for (size_t i = 0; i < n - 1; i++) {
            size_t minAreaIndex = i;

            for (size_t j = i; j < n; j++) {
                if (areas[j] < areas[minAreaIndex]) {
                    minAreaIndex = j;
                }
            }

            if (minAreaIndex != i) {
                std::swap(triangles[i], triangles[minAreaIndex]);
                std::swap(areas[i], areas[minAreaIndex]);
            }
        }

        delete[] areas;
    }

    void printTriangle(const Triangle& triangle) {
        printPoint(triangle.p1);
        printPoint(triangle.p2);
        printPoint(triangle.p3);
    }
}

int main() {
    size_t n;
    std::cin >> n;

    Triangles::Triangle* triangles = new Triangles::Triangle[n];
    for (size_t i = 0; i < n; i++) {
        Triangles::readTriangle(triangles[i]);
    }

    Triangles::sortTrianglesByArea(triangles, n);

    for (size_t i = 0; i < n; i++) {
        Triangles::printTriangle(triangles[i]);
        std::cout << std::endl;
    }

    delete[] triangles;
}
