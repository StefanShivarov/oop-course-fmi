#pragma once
#include <iostream>


namespace {
	const size_t DEFAULT_MATRIX_SIZE = 2;
}

template <typename T>
class Matrix {

	T** data;
	size_t rows = 0;
	size_t cols = 0;

public:

	Matrix();
	Matrix(size_t rows, size_t cols);
	Matrix(const Matrix<T>& other);
	Matrix(Matrix<T>&& other) noexcept;
	~Matrix();

	Matrix<T>& operator=(const Matrix<T>& other);
	Matrix<T>& operator=(Matrix<T>&& other) noexcept;

	void setAt(const size_t x, const size_t y, const T& element);
	const T& getAt(const size_t x, const size_t y) const;

	void transpose();
	void print() const;

private:

	void free();
	void copyFrom(const Matrix<T>& other);
	void move(Matrix<T>&& other);

};

template <typename T>
void Matrix<T>::free() {
	
	for (size_t i = 0; i < rows; i++) {
		delete[] data[i];
	}
	delete[] data;
}

template <typename T>
void Matrix<T>::copyFrom(const Matrix<T>& other) {

	data = new T*[other.rows];

	for (size_t i = 0; i < other.rows; i++) {
		data[i] = new T[other.cols];
		for (size_t j = 0; j < other.cols; j++) {
			data[i][j] = other.data[i][j];
		}
	}

	rows = other.rows;
	cols = other.cols;
}

template <typename T>
void Matrix<T>::move(Matrix<T>&& other) {

	data = other.data;
	rows = other.rows;
	cols = other.cols;
	other.data = nullptr;
	other.rows = other.cols = 0;
}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols): rows(rows), cols(cols) {

	data = new T*[rows];

	for (size_t i = 0; i < rows; i++) {
		data[i] = new T[cols];
	}

}

template <typename T>
Matrix<T>::Matrix(): Matrix(DEFAULT_MATRIX_SIZE, DEFAULT_MATRIX_SIZE) {}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other) {
	copyFrom(other);
}

template <typename T>
Matrix<T>::Matrix(Matrix<T>&& other) noexcept {
	move(std::move(other));
}

template <typename T>
Matrix<T>::~Matrix() {
	free();
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
	
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& other) noexcept {

	if (this != &other) {
		free();
		move(std::move(other));
	}

	return *this;
}

template <typename T>
const T& Matrix<T>::getAt(const size_t x, const size_t y) const {

	if (x >= rows || y >= cols) {
		throw std::length_error("Invalid index!");
	}

	return data[x][y];
}

template <typename T>
void Matrix<T>::setAt(const size_t x, const size_t y, const T& element) {

	if (x >= rows || y >= cols) {
		throw std::length_error("Invalid index!");
	}

	data[x][y] = element;
}

template <typename T>
void Matrix<T>::transpose() {

	T** transposed = new T * [cols];
	for (size_t i = 0; i < cols; i++) {
		transposed[i] = new T[rows];
	}

	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			transposed[j][i] = data[i][j];
		}
	}

	for (size_t i = 0; i < rows; i++) {
		delete[] data[i];
	}
	delete[] data;

	data = transposed;
	size_t temp = rows;
	rows = cols;
	cols = temp;
}

template <typename T>
void Matrix<T>::print() const {

	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {

			std::cout << data[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}