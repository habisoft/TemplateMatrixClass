#include <iostream>
#include "Matrix.hpp"

int main(int argc, char* argv[]) {
    const size_t numRows = 3, numCols = 3;

    Matrix<int> A = Matrix<int>(numRows, numCols);
    
    for (size_t i = 0; i < numRows; ++i) {
        for (size_t j = 0; j < numCols; ++j) {
            A(i, j) = i + j;
        }
    }
    
    A.print("A");

    Matrix<int> B = A;

    B.print("B");

    return 0;
}
