#include <iostream>
#include <fstream>
#include <sstream>

namespace Constants {
    const int MATRIX_DIMENSION = 3;
    const int MAX_ROW_STRING_SIZE = 10;
}

typedef int MatrixRow[Constants::MATRIX_DIMENSION];

struct Matrix {
    MatrixRow rows[Constants::MATRIX_DIMENSION];
};

Matrix multiplyMatrices(const Matrix& m1, const Matrix& m2) {
    Matrix multiplication = {};

    for (int i = 0; i < Constants::MATRIX_DIMENSION; i++) {
        for (int j = 0; j < Constants::MATRIX_DIMENSION; j++) {
            for (int k = 0; k < Constants::MATRIX_DIMENSION; k++) {
                multiplication.rows[i][j] += m1.rows[i][k] * m2.rows[k][j];
            }
        }
    }

    return multiplication;
}

void parseMatrixRow(const char* str, MatrixRow& row) {
    std::stringstream ss(str);
    size_t currentCol = 0;
    for (int i = 0; i < Constants::MATRIX_DIMENSION; i++) {
        ss >> row[currentCol++];
        ss.ignore();
    }
}

Matrix loadMatrixFromFile(const char* fileName) {
    std::ifstream ifs(fileName);
    if (!ifs.is_open()) {
        std::cerr << "Failed to open file " << fileName << '!';
        return {};
    }

    Matrix matrix;

    char rowStr[Constants::MAX_ROW_STRING_SIZE];
    for (int i = 0; i < Constants::MATRIX_DIMENSION; i++) {
        if (i == Constants::MATRIX_DIMENSION - 1) {
            ifs.getline(rowStr, Constants::MAX_ROW_STRING_SIZE);
        }
        else {
            ifs.getline(rowStr, Constants::MAX_ROW_STRING_SIZE, '|');
        }

        parseMatrixRow(rowStr, matrix.rows[i]);
    }

    return matrix;
}

void writeRow(std::ostream& os, const MatrixRow& row) {
    for (int i = 0; i < Constants::MATRIX_DIMENSION; i++) {
        os << row[i];
        if (i != Constants::MATRIX_DIMENSION - 1) {
            os << ',';
        }
    }
}

void writeMatrixToFile(const char* fileName, const Matrix& matrix) {
    std::ofstream ofs(fileName);
    if (!ofs.is_open()) {
        std::cerr << "Failed to open file " << fileName << '!';
        return;
    }

    for (int i = 0; i < Constants::MATRIX_DIMENSION; i++) {
        writeRow(ofs, matrix.rows[i]);
        if (i != Constants::MATRIX_DIMENSION - 1) {
            ofs << '|';
        }
    }
}

int main() {
    Matrix m1 = loadMatrixFromFile("first.txt");
    Matrix m2 = loadMatrixFromFile("second.txt");

    Matrix multiplication = multiplyMatrices(m1, m2);
    
    writeMatrixToFile("result.txt", multiplication);
}
