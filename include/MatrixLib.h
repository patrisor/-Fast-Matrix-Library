#ifndef MATRIXLIB_H
#define MATRIXLIB_H

#include <vector>
#include <thread>
#include <iostream>

/**
 * Matrix Library
 *
 * This header-only library provides a template-based implementation of a 
 * matrix class.
 *
 * Usage example:
 * Matrix<int> A = {{1, 2}, {3, 4}};
 * Matrix<int> B = {{5, 6}, {7, 8}};
 * auto C = A * B;
 * C.print();
 */
template<typename T>
class Matrix {
private:
    int rows, cols;
    std::vector<T> data;

public:
    /* ********************************************************************* */
    /* ************************** Initialization *************************** */
    /* ********************************************************************* */

    /**
     * Constructs a zero-initialized matrix of specific dimensions.
     * 
     * @param rows Number of rows in the matrix.
     * @param cols Number of columns in the matrix.
     */
    Matrix(int rows, int cols) : 
        rows(rows), cols(cols), data(rows * cols, 0) {}

    /**
     * Constructs a matrix from a nested initializer list.
     * 
     * @param init A nested initializer list representing a matrix.
     */
    Matrix(std::initializer_list<std::initializer_list<T>> init) : 
        rows(static_cast<int>(init.size())), 
        cols(init.begin() != init.end() 
            ? static_cast<int>(init.begin()->size()) : 0),
        data(rows * cols) {
        auto it = data.begin();
        for (const auto& row : init) {
            if (row.size() != static_cast<size_t>(cols)) {
                throw std::invalid_argument(
                    "All rows must have the same number of columns."
                );
            }
            it = std::copy(row.begin(), row.end(), it);
        }
    }

    /* ********************************************************************* */
    /* ***************************** Accessors ***************************** */
    /* ********************************************************************* */

    /**
     * Accesses the element at the specified row and column of the matrix.
     * Provides modifiable access.
     * 
     * @param row The zero-based index of the row.
     * @param col The zero-based index of the column.
     * @return Reference to the matrix element.
     */
    T& operator()(int row, int col) {
        return data[row * cols + col];
    }

    /**
     * Accesses the element at the specified row and column of the matrix.
     * Provides read-only access.
     * 
     * @param row The zero-based index of the row.
     * @param col The zero-based index of the column.
     * @return Const reference to the matrix element.
     */
    const T& operator()(int row, int col) const {
        return data[row * cols + col];
    }

    /**
     * Returns the number of rows in the matrix.
     * 
     * @return Integer count of rows.
     */
    int getRows() const { 
        return rows; 
    }

    /**
     * Returns the number of columns in the matrix.
     * 
     * @return Integer count of columns.
     */
    int getCols() const { 
        return cols; 
    }

    /* ********************************************************************* */
    /* ************************ Operator Overloads ************************* */
    /* ********************************************************************* */
    
    /**
     * Compares two matrices for equality.
     * 
     * @param rhs The right-hand side matrix to compare with this matrix.
     * @return true if both matrices are the same size and all corresponding 
     *         elements are equal; false otherwise.
     */
    bool operator==(const Matrix<T>& rhs) const {
        return rows == rhs.rows && cols == rhs.cols && data == rhs.data;
    }

    /* ********************************************************************* */
    /* ************************* Matrix Operations ************************* */
    /* ********************************************************************* */

    /**
     * Multiplies this matrix by another matrix.
     * 
     * @param other The matrix to multiply by.
     * @return A new matrix representing the result of the multiplication.
     */
    Matrix<T> operator*(const Matrix<T>& other) const {
        // Validate matrix dimensions
        if (cols != other.rows) throw std::invalid_argument(
            "Incompatible dimensions for multiplication."
        );
        // Determine the number of rows and columns for the resulting matrix
        Matrix<T> result(rows, other.cols);
        // Launch threads for each block of the resulting matrix
        int blockSize = 128;
        std::vector<std::thread> threads;
        for (int i = 0; i < rows; i += blockSize) {
            for (int j = 0; j < other.cols; j += blockSize) {
                threads.emplace_back(
                    &Matrix::multiplyBlock, 
                    this, i, j, blockSize, 
                    std::cref(other), 
                    std::ref(result)
                );
            }
        }
        // Wait for all threads to complete
        for (auto& thread : threads) {
            thread.join();
        }
        return result;
    }
    
    /**
     * Transposes the matrix.
     * 
     * @return A new matrix that is the transpose of this matrix.
     */
    Matrix<T> transpose() const {
        Matrix<T> result(cols, rows);
        // Loop over the matrix in blocks
        int blockSize = 256;
        std::vector<std::thread> threads;
        for (int i = 0; i < rows; i += blockSize) {
            for (int j = 0; j < cols; j += blockSize) {
                // Launch a new thread for each block
                threads.emplace_back([=, &result]() {
                    transposeBlock(i, j, blockSize, result);
                });
            }
        }
        // Wait for all threads to complete their tasks
        for (auto& thread : threads) {
            thread.join();
        }
        return result;
    }

    /* ********************************************************************* */
    /* ************************** Helper Functions ************************* */
    /* ********************************************************************* */

    /**
     * Helper function to multiply a block of the matrix.
     * Used in multithreaded multiplication algorithm.
     * 
     * @param rowStart The starting row index for the block.
     * @param colStart The starting column index for the block.
     * @param blockSize The size of the block to process.
     * @param other The matrix to multiply with.
     * @param result Reference to the resulting matrix where the block's 
     *               results are stored.
     */
    void multiplyBlock(
        int rowStart, int colStart, int blockSize, 
        const Matrix<T>& other, Matrix<T>& result
    ) const {
        int endRow = std::min(rowStart + blockSize, rows);
        int endCol = std::min(colStart + blockSize, other.getCols());
        for (int i = rowStart; i < endRow; ++i) {
            for (int j = colStart; j < endCol; ++j) {
                T sum = 0;
                for (int k = 0; k < cols; ++k) {
                    sum += (*this)(i, k) * other(k, j);
                }
                result(i, j) = sum;
            }
        }
    }

    /**
     * Helper function to transpose a block of the matrix. 
     * Used in multithreaded transposition algorithm.
     * 
     * @param src The source matrix to transpose from.
     * @param dst The destination matrix to transpose into.
     * @param row Starting row index for the block.
     * @param col Starting column index for the block.
     * @param blockSize Size of the block to transpose.
     */
    void transposeBlock(
        int row, int col, 
        int blockSize, 
        Matrix<T>& result
    ) const {
        for (int i = row; i < std::min(row + blockSize, rows); ++i) {
            for (int j = col; j < std::min(col + blockSize, cols); ++j) {
                result(j, i) = (*this)(i, j);
            }
        }
    }

    /* ********************************************************************* */
    /* *************************** Visualization *************************** */
    /* ********************************************************************* */

    /**
     * Prints the matrix to standard output.
     */
    void print() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << (*this)(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }
};

#endif // MATRIXLIB_H