#include <iostream>
#include "Matrix.hpp"

int main()
{

	Matrix<int> test1(2, 2);
	test1.setAt(0, 0, 5);
	test1.setAt(0, 1, 3);
	test1.setAt(1, 0, 4);
	test1.setAt(1, 1, 1);
	/*
	(5,3)
	(4,1)
	*/
	test1.print();
	test1.transpose();
	/*
	(5,4)
	(3,1)
	*/
	test1.print();
	std::cout << test1.getAt(0, 1); //4

}
