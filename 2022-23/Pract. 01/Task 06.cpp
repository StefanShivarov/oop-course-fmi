#include <iostream>
#include <cmath>

struct Point {
	double x = 0;
	double y = 0;
};

void readPoint(Point& point) {
	std::cout << "Enter point coordinates: " << std::endl;
	std::cout << "x: ";
	std::cin >> point.x;
	std::cout << "y: ";
	std::cin >> point.y;
}

void printPoint(const Point& point) {
	std::cout << "( " << point.x << ", " << point.y << " )" << std::endl;
}

double distanceFromCenter(const Point& point) {
	return sqrt(point.x * point.x + point.y * point.y);
}

double distanceBetweenTwoPoints(const Point& p1, const Point& p2) {
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

int getQuadrant(const Point& p) {

	if (p.x > 0 && p.y > 0) {
		return 1;
	}
	else if (p.x > 0 && p.y < 0) {
		return 2;
	}
	else if (p.x < 0 && p.y < 0) {
		return 3;
	}
	else if (p.x < 0 && p.y > 0) {
		return 4;
	}
	return 0;
}

void isOnCircle(const Point& point, double circleRadius) {

	if (distanceFromCenter(point) == sqrt(circleRadius)) {
		std::cout << "Point lies on the circle" << std::endl;
	}
	else if (distanceFromCenter(point) < sqrt(circleRadius)) {
		std::cout << "Point lies inside the circle" << std::endl;
	}
	else {
		std::cout << "Point lies outside the circle" << std::endl;
	}
}

int main() {

	Point p{ 4, 5 };
	printPoint(p);
	std::cout << distanceFromCenter(p);
	isOnCircle(p, 41);

	Point p2;
	readPoint(p2);
	printPoint(p2);

	std::cout << distanceBetweenTwoPoints(p, p2);
}