#include "Matrix.h"

void Matrix::free() {
    for (size_t i = 0; i < rows; i++) {
        delete[] data[i];
    }
    delete[] data;
    data = nullptr;
    rows = cols = 0;
}

void Matrix::copyFrom(const Matrix& other) {
    rows = other.rows;
    cols = other.cols;
    data = new int* [rows];
    for (size_t i = 0; i < rows; i++) {
        data[i] = new int[cols];
        for (size_t j = 0; j < cols; j++) {
            data[i][j] = other.data[i][j];
        }
    }
}

Matrix::Matrix() : Matrix(DEFAULT_DIMENSION, DEFAULT_DIMENSION) {}

Matrix::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
    data = new int* [rows];
    for (size_t i = 0; i < rows; i++) {
        data[i] = new int[cols] {};
    }
}

Matrix::Matrix(const Matrix& other) {
    copyFrom(other);
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Matrix::~Matrix() {
    free();
}

size_t Matrix::getRows() const {
    return rows;
}

size_t Matrix::getCols() const {
    return cols;
}

Matrix& Matrix::operator+=(const Matrix& other) {
    if (rows != other.rows || cols != other.cols) {
        return *this;
    }

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            data[i][j] += other.data[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
    if (rows != other.rows || cols != other.cols) {
        return *this;
    }

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            data[i][j] -= other.data[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) {
    if (cols != other.rows) {
        return *this;
    }

    Matrix temp(rows, other.cols);
    for (size_t i = 0; i < temp.rows; i++) {
        for (size_t j = 0; j < temp.cols; j++) {
            for (size_t k = 0; k < cols; k++) {
                temp[i][j] += data[i][k] * other[k][j];
            }
        }
    }

    *this = temp;
    return *this;
}

Matrix& Matrix::operator*=(int scalar) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            data[i][j] *= scalar;
        }
    }
    return *this;
}

int* Matrix::operator[](size_t index) {
    if (index >= rows) {
        return nullptr;
    }
    return data[index];
}

const int* Matrix::operator[](size_t index) const {
    if (index >= rows) {
        return nullptr;
    }
    return data[index];
}

Matrix::operator bool() const {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (data[i][j] != 0) {
                return true;
            }
        }
    }
    return false;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
    Matrix result(lhs);
    result += rhs;
    return result;
}

Matrix operator-(const Matrix& lhs, const Matrix& rhs) {
    Matrix result(lhs);
    result -= rhs;
    return result;
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
    Matrix result(lhs);
    result *= rhs;
    return result;
}

Matrix operator*(const Matrix& matrix, int scalar) {
    Matrix result(matrix);
    result *= scalar;
    return result;
}

Matrix operator*(int scalar, const Matrix& matrix) {
    return matrix * scalar;
}

bool operator==(const Matrix& lhs, const Matrix& rhs) {
    size_t rows = lhs.getRows();
    size_t cols = lhs.getCols();
    if (rows != rhs.getRows() || cols != rhs.getCols()) {
        return false;
    }

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (lhs[i][j] != rhs[i][j]) {
                return false;
            }
        }
    }

    return true;
}

bool operator!=(const Matrix& lhs, const Matrix& rhs) {
    return !(lhs == rhs);
}

std::istream& operator>>(std::istream& is, Matrix& matrix) {
    size_t rows, cols;
    is >> rows >> cols;
    matrix = Matrix(rows, cols);

    for (size_t i = 0; i < matrix.rows; i++) {
        for (size_t j = 0; j < matrix.cols; j++) {
            is >> matrix[i][j];
        }
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (size_t i = 0; i < matrix.rows; i++) {
        for (size_t j = 0; j < matrix.cols; j++) {
            os << matrix[i][j] << ' ';
        }
        os << std::endl;
    }
    return os;
}
