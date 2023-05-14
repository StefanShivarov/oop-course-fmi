#include <iostream>

int** initMatrix(const int rows, const int cols) {

	int** matrix = new int*[rows];
	for (int i = 0; i < rows; i++) {
		matrix[i] = new int[cols];
	}
	return matrix;
}

void readMatrix(int** matrix, const int rows, const int cols) {

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			std::cin >> matrix[i][j];
		}
	}
}

int** transposeMatrix(int** matrix, const int rows, const int cols) {

	int** transposed = initMatrix(cols, rows);

	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			transposed[i][j] = matrix[j][i];
		}
	}

	return transposed;
}

void printMatrix(int** matrix, const int rows, const int cols) {

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void deleteMatrix(int** matrix, const int rows) {

	for (int i = 0; i < rows; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

int main() {

	int N, M;
	std::cin >> N >> M;

	int** matrix = initMatrix(N, M);
	readMatrix(matrix, N, M);

	int** transposedMatrix = transposeMatrix(matrix, N, M);
	printMatrix(transposedMatrix, M, N);
}