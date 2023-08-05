#include <iostream>

struct Point {

	int x = 0;
	int y = 0;
};

double getDistanceBetweenTwoPoints(const Point& p1, const Point& p2) {

	return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}

void readPoint(Point& point) {

	std::cin >> point.x;
	std::cin >> point.y;
}

void printPoint(const Point& point) {

	std::cout << "x: " << point.x << " y: " << point.y << std::endl;
}

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

	double sideA = getDistanceBetweenTwoPoints(triangle.p2, triangle.p3);
	double sideB = getDistanceBetweenTwoPoints(triangle.p1, triangle.p3);
	double sideC = getDistanceBetweenTwoPoints(triangle.p1, triangle.p2);
	double halfPerimeter = (sideA + sideB + sideC) / 2;

	return sqrt(halfPerimeter*(halfPerimeter - sideA)*(halfPerimeter - sideB)*(halfPerimeter - sideC));
}

void printTriangle(const Triangle& triangle) {

	printPoint(triangle.p1);
	printPoint(triangle.p2);
	printPoint(triangle.p3);
	std::cout << getTriangleArea(triangle) << std::endl;
}

void swapTriangles(Triangle& t1, Triangle& t2) {

	Triangle temp = t1;
	t1 = t2;
	t2 = temp;
}

void sortTrianglesByArea(Triangle* trianglesArr, size_t n) {

	for (int i = 0; i < n - 1; i++) {

		int minIndex = i;

		for (int j = i + 1; j < n; j++) {

			if (getTriangleArea(trianglesArr[j]) < getTriangleArea(trianglesArr[minIndex])) {
				minIndex = j;
			}
		}

		if (minIndex != i) {
			swapTriangles(trianglesArr[i], trianglesArr[minIndex]);
		}
	}
}

int main() {

	size_t N;
	std::cin >> N;

	Triangle* triangles = new Triangle[N];

	for (int i = 0; i < N; i++) {
		readTriangle(triangles[i]);
	}

	sortTrianglesByArea(triangles, N);

	for (int i = 0; i < N; i++) {
		printTriangle(triangles[i]);
	}

	delete[] triangles;
}