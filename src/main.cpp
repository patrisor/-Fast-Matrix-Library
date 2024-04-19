#include <iostream>
#include <cassert>

#include "MatrixLib.h"

void testMatrixMultiplication() {
    std::cout << "Testing Matrix Multiplication..." << std::endl;

    // Identity Matrix Test
    Matrix<int> I = {
        {1, 0}, 
        {0, 1}
    };
    Matrix<int> M = {
        {2, 3}, 
        {4, 5}
    };
    assert((M * I) == M);

    // Zero Matrix Test
    Matrix<int> Zero = {
        {0, 0}, 
        {0, 0}
    };
    assert((M * Zero) == Zero);

    // Rectangular Matrices Test
    Matrix<int> A = {
        {1, 2, 3}
    };
    Matrix<int> B = {
        {1}, 
        {2}, 
        {3}
    };
    Matrix<int> ExpectedProduct = {
        {14}
    };
    assert((A * B) == ExpectedProduct);

    // Symmetric Result Test
    Matrix<int> X = {
        {1, 2},
        {3, 4}
    };
    Matrix<int> Y = {
        {2, 0},
        {1, 2}
    };
    // Since not commutative, just print to demonstrate
    // std::cout << "Matrix X * Y:" << std::endl;
    // (X * Y).print();
    // std::cout << "Matrix Y * X:" << std::endl;
    // (Y * X).print();

    // Known Result Test
    Matrix<int> KnownA = {
        {1, 2},
        {3, 4}
    };
    Matrix<int> KnownB = {
        {2, 0},
        {1, 2}
    };
    Matrix<int> KnownResult = {
        {4, 4},
        {10, 8}
    };
    assert((KnownA * KnownB) == KnownResult);

    std::cout << "Multiplication tests completed successfully." << std::endl;
}

void testMatrixTransposition() {
    std::cout << "Testing Matrix Transposition..." << std::endl;

    // Square Matrix Test
    Matrix<int> squareMatrix = {
        {1, 2},
        {3, 4}
    };
    Matrix<int> expectedSquareTranspose = {
        {1, 3},
        {2, 4}
    };
    assert(squareMatrix.transpose() == expectedSquareTranspose);

    // Rectangular Matrix Test
    Matrix<int> rectangularMatrix = {
        {1, 2, 3},
        {4, 5, 6}
    };
    Matrix<int> expectedRectangularTranspose = {
        {1, 4},
        {2, 5},
        {3, 6}
    };
    assert(rectangularMatrix.transpose() == expectedRectangularTranspose);

    // Single Row Test
    Matrix<int> singleRow = {
        {1, 2, 3}
    };
    Matrix<int> expectedSingleRowTranspose = {
        {1},
        {2},
        {3}
    };
    assert(singleRow.transpose() == expectedSingleRowTranspose);

    // Single Column Test
    Matrix<int> singleColumn = {
        {1},
        {2},
        {3}
    };
    Matrix<int> expectedSingleColumnTranspose = {
        {1, 2, 3}
    };
    assert(singleColumn.transpose() == expectedSingleColumnTranspose);

    // Identity Matrix Test
    Matrix<int> identityMatrix = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    assert(identityMatrix.transpose() == identityMatrix);

    // Zero Matrix Test
    Matrix<int> zeroMatrix = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    assert(zeroMatrix.transpose() == zeroMatrix);

    std::cout << "Transposition tests completed successfully." << std::endl;
}

void testMatrixPerformance() {
    std::cout << "Testing Matrix Performance..." << std::endl;
    const int size = 1000;
    Matrix<int> largeMatrix(size, size);
    // Testing Multiplication Performance
    auto startMultiplication = std::chrono::high_resolution_clock::now();
    Matrix<int> productMatrix = largeMatrix * largeMatrix;
    auto endMultiplication = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> multiplicationDuration = 
        endMultiplication - startMultiplication;
    std::cout << "Multiplication of " << size << "x" << size << " matrix took "
              << multiplicationDuration.count() << " milliseconds." 
              << std::endl;
    // Testing Transposition Performance
    auto startTransposition = std::chrono::high_resolution_clock::now();
    Matrix<int> transposedLargeMatrix = largeMatrix.transpose();
    auto endTransposition = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> transpositionDuration = 
        endTransposition - startTransposition;
    std::cout << "Transposition of " << size << "x" << size << " matrix took "
              << transpositionDuration.count() << " milliseconds." 
              << std::endl;
}

int main() {
    // Run tests
    testMatrixMultiplication();
    std::cout << std::endl;
    testMatrixTransposition();
    std::cout << std::endl;
    testMatrixPerformance();
    // End tests
    std::cout << std::endl;
    std::cout << "All tests passed!" << std::endl;
    return 0;
}