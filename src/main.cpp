#include "MatrixLib.h"

#include <iostream>

// ANSI escape sequences for text formatting
const std::string BOLD = "\033[1m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string RESET = "\033[0m";

/* ********************************************************************* */
/* ******************** Matrix Multiplication Tests ******************** */
/* ********************************************************************* */

/**
 * Test for identity matrix multiplication
 */
void testIdentityMatrixMultiplication() {
    std::cout << BOLD << "\t• Identity Matrix Test:" << RESET 
              << " Demonstrate that (M * I) = M\n";
    // Define matrices
    Matrix<int> M = {
        {2, 3}, 
        {4, 5}
    };
    Matrix<int> I = {
        {1, 0}, 
        {0, 1}
    };
    Matrix<int> MI = M * I;
    // Print matrices
    std::cout << BOLD << "\t\t‣ Matrix M:" << RESET << "\n";
    M.print(18);
    std::cout << BOLD << "\t\t‣ Identity Matrix I:" << RESET << "\n";
    I.print(18);
    // Perform test
    if (MI == M) { // Success
        std::cout << "\t\t‣ " << GREEN + BOLD << "Test Passed" << RESET + GREEN
                  << ": MI = M" << RESET << "\n";
        std::cout << GREEN + BOLD << "\t\t\t◦ Matrix MI:" << RESET << "\n";
        MI.print(26, GREEN);
    } else { // Failure
        std::cout << "\t\t‣ " << RED + BOLD << "Test Failed" << RESET + RED
                  << ": MI != M" << RESET << "\n";
        std::cout << RED + BOLD << "\t\t\t◦ Matrix MI:" << RESET << "\n";
        MI.print(26, RED);
        std::exit(EXIT_FAILURE);
    }
}

/**
 * Test for multiplication with zero matrix
 */
void testZeroMatrixMultiplication() {
    std::cout << BOLD << "\t• Zero Matrix Test:" << RESET 
              << " Demonstrate that (M * Zero) = Zero\n";
    // Define matrices
    Matrix<int> M = {
        {2, 3}, 
        {4, 5}
    };
    Matrix<int> Zero = {
        {0, 0}, 
        {0, 0}
    };
    Matrix<int> MZ = M * Zero;
    // Print matrices
    std::cout << BOLD << "\t\t‣ Matrix M:" << RESET << "\n";
    M.print(18);
    std::cout << BOLD << "\t\t‣ Matrix Zero (Z):" << RESET << "\n";
    Zero.print(18);
    // Perform test
    if (MZ == Zero) { // Success
        std::cout << "\t\t‣ " << GREEN + BOLD << "Test Passed" << RESET + GREEN
                  << ": MZ = Z" << RESET << "\n";
        std::cout << GREEN + BOLD << "\t\t\t◦ Matrix MZ (M * Zero):" 
                  << RESET << "\n";
        MZ.print(26, GREEN);
    } else { // Failure
        std::cout << "\t\t‣ " << RED + BOLD << "Test Failed" << RESET + RED 
                  << ": MZ != Z" << RESET << "\n";
        std::cout << RED + BOLD << "\t\t\t◦ Matrix MZ (M * Zero):" 
                  << RESET << "\n";
        MZ.print(26, RED);
        std::exit(EXIT_FAILURE);
    }
}

/**
 * Test for rectangular matrix multiplication.
 */
void testRectangularMatrixMultiplication() {
    std::cout << BOLD << "\t• Rectangular Matrix Test:" << RESET 
              << " Demonstrate that (A * B) = Expected Result\n";
    // Define matrices
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
    Matrix<int> Result = A * B;
    // Print matrices
    std::cout << BOLD << "\t\t‣ Matrix A:" << RESET << "\n";
    A.print(18);
    std::cout << BOLD << "\t\t‣ Matrix B:" << RESET << "\n";
    B.print(18);
    std::cout << BOLD << "\t\t‣ Expected Result (A * B):" << RESET << "\n";
    ExpectedProduct.print(18);
    // Perform test
    if (Result == ExpectedProduct) { // Success
        std::cout << "\t\t‣ " << GREEN + BOLD << "Test Passed!" 
                  << RESET << "\n";
        std::cout << GREEN + BOLD << "\t\t\t◦ Matrix Result (A * B):" 
                  << RESET << "\n";
        Result.print(26, GREEN);
    } else { // Failure
        std::cout << "\t\t‣ " << RED + BOLD << "Test Failed!" << RESET << "\n";
        std::cout << RED + BOLD << "\t\t\t◦ Matrix Result (A * B):" 
                  << RESET << "\n";
        Result.print(26, RED);
        std::exit(EXIT_FAILURE);
    }
}

/**
 * Test to demonstrate that multiplication is not commutative.
 */
void testSymmetricResult() {
    std::cout << BOLD << "\t• Symmetric Result Test:" << RESET 
              << " Demonstrate that XY != YX\n";
    // Define matrices
    Matrix<int> X = {
        {1, 2}, 
        {3, 4}
    };
    Matrix<int> Y = {
        {2, 0}, 
        {1, 2}
    };
    Matrix<int> XY = X * Y;
    Matrix<int> YX = Y * X;
    // Print matrices
    std::cout << BOLD << "\t\t‣ Matrix X:" << RESET << "\n";
    X.print(18);
    std::cout << BOLD << "\t\t‣ Matrix Y:" << RESET << "\n";
    Y.print(18);
    // Perform test
    if (XY != YX) { // Success
        std::cout << "\t\t‣ " << GREEN + BOLD << "Test Passed" << RESET + GREEN
                  << ": XY != YX" << RESET << "\n";
        std::cout << GREEN + BOLD << "\t\t\t◦ Matrix XY (X * Y):" 
                  << RESET << "\n";
        XY.print(26, GREEN);
        std::cout << GREEN + BOLD << "\t\t\t◦ Matrix YX (Y * X):" 
                  << RESET << "\n";
        YX.print(26, GREEN);
    } else { // Failure
        std::cout << "\t\t‣ " << RED + BOLD << "Test Failed" << RESET + RED 
                  << ": XY = YX" << RESET << "\n";
        std::cout << RED + BOLD << "\t\t\t◦ Matrix XY (X * Y):" 
                  << RESET << "\n";
        XY.print(26, RED);
        std::cout << RED + BOLD << "\t\t\t◦ Matrix YX (Y * X):" 
                  << RESET << "\n";
        YX.print(26, RED);
        std::exit(EXIT_FAILURE);
    }
}

/**
 * Test for known matrix multiplication results.
 */
void testKnownResultMultiplication() {
    std::cout << BOLD << "\t• Known Result Test:" << RESET 
              << " Demonstrate that Matrix Result = Known Result\n";
    // Define matrices
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
    Matrix<int> Result = KnownA * KnownB;
    // Print matrices
    std::cout << BOLD << "\t\t‣ Matrix KnownA:" << RESET << "\n";
    KnownA.print(18);
    std::cout << BOLD << "\t\t‣ Matrix KnownB:" << RESET << "\n";
    KnownB.print(18);
    std::cout << BOLD << "\t\t‣ Known Result (KnownA * KnownB):" 
              << RESET << "\n";
    KnownResult.print(18);
    // Perform test
    if (Result == KnownResult) { // Success
        std::cout << "\t\t‣ " << GREEN + BOLD << "Test Passed" << RESET + GREEN
                  << ": Matrix Result = Known Result" << RESET << "\n";
        std::cout << GREEN + BOLD << "\t\t\t◦ Matrix Result (KnownA * KnownB):"
                  << RESET << "\n";
        Result.print(26, GREEN);
    } else { // Failure
        std::cout << "\t\t‣ " << RED + BOLD << "Test Failed" << RESET + RED 
                  << ": Matrix Result != Known Result" << RESET << "\n";
        std::cout << RED + BOLD << "\t\t\t◦ Matrix Result (KnownA * KnownB):"
                  << RESET << "\n";
        Result.print(26, RED);
        std::exit(EXIT_FAILURE);
    }
}

/**
 * Runs all the tests for matrix multiplication.
 */
void testMatrixMultiplication() {
    std::cout << BOLD << "Testing Matrix Multiplication:" << RESET << "\n";
    testIdentityMatrixMultiplication();
    testZeroMatrixMultiplication();
    testRectangularMatrixMultiplication();
    testSymmetricResult();
    testKnownResultMultiplication();
    std::cout << "\t• " << GREEN + BOLD
              << "Multiplication Tests completed successfully!" 
              << RESET << "\n";
}

/* ********************************************************************* */
/* ******************** Matrix Transposition Tests ********************* */
/* ********************************************************************* */

/**
 * Test for square matrix transposition.
 * Verifies that the transpose of a square matrix is correct.
 */
void testSquareMatrixTransposition() {
    std::cout << BOLD << "\t• Square Matrix Test:" << RESET 
              << " Demonstrate that M^T = E^T\n";
    // Define matrices
    Matrix<int> squareMatrix = {
        {1, 2},
        {3, 4}
    };
    Matrix<int> expectedSquareTranspose = {
        {1, 3},
        {2, 4}
    };
    Matrix<int> resultingTranspose = squareMatrix.transpose();
    // Print matrices
    std::cout << BOLD << "\t\t‣ Matrix M:" << RESET << "\n";
    squareMatrix.print(18);
    std::cout << BOLD << "\t\t‣ Matrix E^T:" << RESET << "\n";
    expectedSquareTranspose.print(18);
    // Perform test
    if (resultingTranspose == expectedSquareTranspose) { // Success
        std::cout << GREEN + BOLD << "\t\t‣ Test Passed" << RESET + GREEN
                  << ": M^T = E^T" << RESET << "\n";
        std::cout << GREEN + BOLD << "\t\t\t◦ Matrix M^T:" << RESET << "\n";
        resultingTranspose.print(26, GREEN);
    } else { // Failure
        std::cout << RED + BOLD << "\t\t‣ Test Failed" << RESET + RED
                  << ": M^T != E^T" << RESET << "\n";
        std::cout << RED + BOLD << "\t\t\t◦ Matrix M^T:" << RESET << "\n";
        resultingTranspose.print(26, RED);
        std::exit(EXIT_FAILURE);
    }
}

/**
 * Test for rectangular matrix transposition.
 * Verifies that the transpose of a rectangular matrix is correct.
 */
void testRectangularMatrixTransposition() {
    std::cout << BOLD << "\t• Rectangular Matrix Test:" << RESET 
              << " Demonstrate that M^T = E^T\n";
    // Define matrices
    Matrix<int> rectangularMatrix = {
        {1, 2, 3},
        {4, 5, 6}
    };
    Matrix<int> expectedRectangularTranspose = {
        {1, 4},
        {2, 5},
        {3, 6}
    };
    Matrix<int> resultingTranspose = rectangularMatrix.transpose();
    // Print matrices
    std::cout << BOLD << "\t\t‣ Matrix M:" << RESET << "\n";
    rectangularMatrix.print(18);
    std::cout << BOLD << "\t\t‣ Matrix E^T:" << RESET << "\n";
    expectedRectangularTranspose.print(18);
    // Perform test
    if (resultingTranspose == expectedRectangularTranspose) { // Success
        std::cout << GREEN + BOLD << "\t\t‣ Test Passed" << RESET + GREEN
                  << ": M^T = E^T" << RESET << "\n";
        std::cout << GREEN + BOLD << "\t\t\t◦ Matrix M^T:" << RESET << "\n";
        resultingTranspose.print(26, GREEN);
    } else { // Failure
        std::cout << RED + BOLD << "\t\t‣ Test Failed" << RESET + RED
                  << ": M^T != E^T" << RESET << "\n";
        std::cout << RED + BOLD << "\t\t\t◦ Matrix M^T:" << RESET << "\n";
        resultingTranspose.print(26, RED);
        std::exit(EXIT_FAILURE);
    }
}

/**
 * Test for single-row matrix transposition.
 * Verifies that the transpose of a single-row matrix is correct.
 */
void testSingleRowTransposition() {
    std::cout << BOLD << "\t• Single Row Test:" << RESET 
              << " Demonstrate that M^T = E^T\n";
    // Define matrices
    Matrix<int> singleRow = {
        {1, 2, 3}
    };
    Matrix<int> expectedSingleRowTranspose = {
        {1},
        {2},
        {3}
    };
    Matrix<int> resultingTranspose = singleRow.transpose();
    // Print matrices
    std::cout << BOLD << "\t\t‣ Matrix M:" << RESET << "\n";
    singleRow.print(18);
    std::cout << BOLD << "\t\t‣ Matrix E^T:" << RESET << "\n";
    expectedSingleRowTranspose.print(18);
    // Perform test
    if (resultingTranspose == expectedSingleRowTranspose) { // Success
        std::cout << GREEN + BOLD << "\t\t‣ Test Passed" << RESET + GREEN
                  << ": M^T = E^T" << RESET << "\n";
        std::cout << GREEN + BOLD << "\t\t\t◦ Matrix M^T:" << RESET << "\n";
        resultingTranspose.print(26, GREEN);
    } else { // Failure
        std::cout << RED + BOLD << "\t\t‣ Test Failed" << RESET + RED
                  << ": M^T != E^T" << RESET << "\n";
        std::cout << RED + BOLD << "\t\t\t◦ Matrix M^T:" << RESET << "\n";
        resultingTranspose.print(26, RED);
        std::exit(EXIT_FAILURE);
    }
}

/**
 * Test for single-column matrix transposition.
 * Verifies that the transpose of a single-column matrix is correct.
 */
void testSingleColumnTransposition() {
    std::cout << BOLD << "\t• Single Column Test:" << RESET 
              << " Demonstrate that M^T = E^T\n";
    // Define matrices
    Matrix<int> singleColumn = {
        {1},
        {2},
        {3}
    };
    Matrix<int> expectedSingleColumnTranspose = {
        {1, 2, 3}
    };
    Matrix<int> resultingTranspose = singleColumn.transpose();
    // Print matrices
    std::cout << BOLD << "\t\t‣ Matrix M:" << RESET << "\n";
    singleColumn.print(18);
    std::cout << BOLD << "\t\t‣ Matrix E^T:" << RESET << "\n";
    expectedSingleColumnTranspose.print(18);
    // Perform test
    if (resultingTranspose == expectedSingleColumnTranspose) { // Success
        std::cout << GREEN + BOLD << "\t\t‣ Test Passed" << RESET + GREEN
                  << ": M^T = E^T" << RESET << "\n";
        std::cout << GREEN + BOLD << "\t\t\t◦ Matrix M^T:" << RESET << "\n";
        resultingTranspose.print(26, GREEN);
    } else { // Failure
        std::cout << RED + BOLD << "\t\t‣ Test Failed" << RESET + RED
                  << ": M^T != E^T" << RESET << "\n";
        std::cout << RED + BOLD << "\t\t\t◦ Matrix M^T:" << RESET << "\n";
        resultingTranspose.print(26, RED);
        std::exit(EXIT_FAILURE);
    }
}

/**
 * Test for identity matrix transposition.
 * Verifies that the transpose of an identity matrix is itself.
 */
void testIdentityMatrixTransposition() {
    std::cout << BOLD << "\t• Identity Matrix Test:" << RESET 
              << " Demonstrate that I^T = I\n";
    // Define matrices
    Matrix<int> identityMatrix = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    Matrix<int> resultingTranspose = identityMatrix.transpose();
    // Print matrices
    std::cout << BOLD << "\t\t‣ Matrix I:" << RESET << "\n";
    identityMatrix.print(18);
    // Perform test
    if (resultingTranspose == identityMatrix) { // Success
        std::cout << GREEN + BOLD << "\t\t‣ Test Passed" << RESET + GREEN
                  << ": I^T = I" << RESET << "\n";
        std::cout << GREEN + BOLD << "\t\t\t◦ Matrix I^T:" << RESET << "\n";
        resultingTranspose.print(26, GREEN);
    } else { // Failure
        std::cout << RED + BOLD << "\t\t‣ Test Failed" << RESET + RED
                  << ": I^T != I" << RESET << "\n";
        std::cout << RED + BOLD << "\t\t\t◦ Matrix I^T:" << RESET << "\n";
        resultingTranspose.print(26, RED);
        std::exit(EXIT_FAILURE);
    }
}

/**
 * Test for zero matrix transposition.
 * Verifies that the transpose of a zero matrix is also a zero matrix.
 */
void testZeroMatrixTransposition() {
    std::cout << BOLD << "\t• Zero Matrix Test:" << RESET 
              << " Demonstrate that Z^T = Z\n";
    // Define matrices
    Matrix<int> zeroMatrix = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    Matrix<int> resultingTranspose = zeroMatrix.transpose();
    // Print matrices
    std::cout << BOLD << "\t\t‣ Matrix Z:" << RESET << "\n";
    zeroMatrix.print(18);
    // Perform test
    if (resultingTranspose == zeroMatrix) { // Success
        std::cout << GREEN + BOLD << "\t\t‣ Test Passed" << RESET + GREEN
                  << ": Z^T = Z" << RESET << "\n";
        std::cout << GREEN + BOLD << "\t\t\t◦ Matrix Z^T:" << RESET << "\n";
        resultingTranspose.print(26, GREEN);
    } else { // Failure
        std::cout << RED + BOLD << "\t\t‣ Test Failed" << RESET + RED
                  << ": Z^T = Z" << RESET << "\n";
        std::cout << RED + BOLD << "\t\t\t◦ Matrix Z^T:" << RESET << "\n";
        resultingTranspose.print(26, RED);
        std::exit(EXIT_FAILURE);
    }
}

/**
 * Run all the matrix transposition tests.
 */
void testMatrixTransposition() {
    std::cout << BOLD << "Testing Matrix Transposition:" << RESET << "\n";
    testSquareMatrixTransposition();
    testRectangularMatrixTransposition();
    testSingleRowTransposition();
    testSingleColumnTransposition();
    testIdentityMatrixTransposition();
    testZeroMatrixTransposition();
    std::cout << "\t• " << GREEN + BOLD
              << "Transposition Tests completed successfully!" 
              << RESET << "\n";
}

/* ********************************************************************* */
/* ********************** Matrix Edge Case Tests *********************** */
/* ********************************************************************* */

/**
 * Test operations on an empty matrix.
 */
void testEmptyMatrix() {
    std::cout << BOLD << "\t• Empty Matrix Test:" << RESET 
              << " Ensure operations on an empty matrix"
              << " doesn't cause crashes\n";
    // Create empty matrices
    Matrix<int> empty(0, 0);
    Matrix<int> anotherEmpty(0, 0);
    // Print matrices
    std::cout << BOLD << "\t\t‣ Empty Matrix:" << RESET << "\n";
    empty.print(18);
    // Test transpose operation on empty matrix
    try {
        Matrix<int> transposed = empty.transpose();
        std::cout << "\t\t‣ " << GREEN + BOLD << "Test Passed" << RESET + GREEN
                  << ": No crash on transpose" << RESET << "\n";
    } catch (const std::exception& e) {
        std::cout << "\t\t‣ " << RED + BOLD << "Test Failed" << RESET + RED
                  << ": Exception on transpose - " << e.what() 
                  << RESET << "\n";
        std::exit(EXIT_FAILURE);
    }
    // Test multiplication operation on empty matrices
    try {
        Matrix<int> product = empty * anotherEmpty;
        std::cout << "\t\t‣ " << GREEN + BOLD << "Test Passed" << RESET + GREEN
                  << ": No crash on multiplication" << RESET << "\n";
    } catch (const std::exception& e) {
        std::cout << "\t\t‣ " << RED + BOLD << "Test Failed" << RESET + RED
                  << ": Exception on multiplication - " << e.what() 
                  << RESET << "\n";
        std::exit(EXIT_FAILURE);
    }
}

/**
 * Test invalid matrix multiplication.
 */
void testInvalidMatrixMultiplication() {
    std::cout << BOLD << "\t• Invalid Multiplication Test:" << RESET 
              << " Ensure invalid multiplication (A * B)"
              << " throws an exception\n";
    // Define matrices with incompatible dimensions
    Matrix<int> A = {{1, 2, 3}};
    Matrix<int> B = {{1, 2}};
    // Print matrices
    std::cout << BOLD << "\t\t‣ Matrix A:" << RESET << "\n";
    A.print(18);
    std::cout << BOLD << "\t\t‣ Matrix B:" << RESET << "\n";
    B.print(18);
    // Attempt invalid multiplication
    try { // This should throw an exception
        Matrix<int> result = A * B;
        std::cout << "\t\t‣ " << RED + BOLD << "Test Failed" << RESET + RED
                  << ": No exception on invalid multiplication" 
                  << RESET << "\n";
        std::exit(EXIT_FAILURE);
    } catch (const std::invalid_argument& e) {
        std::cout << "\t\t‣ " << GREEN + BOLD << "Test Passed" << RESET + GREEN
                  << ": Exception thrown on invalid multiplication" 
                  << RESET << "\n";
    }
}

/**
 * Test invalid matrix transposition.
 */
void testInvalidMatrixTransposition() {
    std::cout << BOLD << "\t• Invalid Transposition Test:" << RESET 
              << " Ensure invalid transposition does not cause crashes\n";
    try { // This should throw an exception
        // Define a non-rectangular matrix using nested initializer lists
        Matrix<int> invalidMatrix = {{1, 2, 3}, {4, 5}};
        std::cout << "\t\t‣ " << RED + BOLD << "Test Failed" << RESET + RED
                  << ": No exception on invalid transposition" 
                  << RESET << "\n";
        std::exit(EXIT_FAILURE);
    } catch (const std::invalid_argument& e) {
        std::cout << "\t\t‣ " << GREEN + BOLD << "Test Passed" << RESET + GREEN
                  << ": Exception thrown on invalid transposition - " 
                  << e.what() << RESET << "\n";
    }
}

/**
 * Run all the matrix edge case tests.
 */
void testMatrixEdgeCases() {
    std::cout << BOLD << "Testing Matrix Edge Cases:" << RESET << "\n";
    testEmptyMatrix();
    testInvalidMatrixMultiplication();
    testInvalidMatrixTransposition();
    std::cout << "\t• " << GREEN + BOLD
              << "Matrix Edge Case Tests completed successfully!" 
              << RESET << "\n";
}

/* ********************************************************************* */
/* ********************* Matrix Performance Tests ********************** */
/* ********************************************************************* */

void testMatrixPerformance() {
    std::cout << BOLD << "Testing Matrix Performance:" << RESET << "\n";
    const int size = 1000;
    Matrix<int> largeMatrix(size, size);
    // Testing Multiplication Performance
    auto startMultiplication = std::chrono::high_resolution_clock::now();
    Matrix<int> productMatrix = largeMatrix * largeMatrix;
    auto endMultiplication = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> multiplicationDuration = 
        endMultiplication - startMultiplication;
    std::cout << "\t• Multiplication of " 
              << BOLD << size << "x" << size << RESET << " matrix took " 
              << BOLD << multiplicationDuration.count() << RESET
              << " milliseconds.\n";
    // Testing Transposition Performance
    auto startTransposition = std::chrono::high_resolution_clock::now();
    Matrix<int> transposedLargeMatrix = largeMatrix.transpose();
    auto endTransposition = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> transpositionDuration = 
        endTransposition - startTransposition;
    std::cout << "\t• Transposition of " 
              << BOLD << size << "x" << size << RESET << " matrix took " 
              << BOLD << transpositionDuration.count() << RESET
              << " milliseconds.\n";
}

int main() {
    // Run Matrix Edge Case tests
    testMatrixEdgeCases();
    std::cout << "\n";
    // Run Matrix Multiplication tests
    testMatrixMultiplication();
    std::cout << "\n";
    // Run Matrix Transposition tests
    testMatrixTransposition();
    std::cout << "\n";
    // Run Matrix Performance tests
    testMatrixPerformance();
    std::cout << "\n";
    // End tests
    std::cout << GREEN + BOLD << "All Tests Passed!" << RESET << "\n";
    return 0;
}