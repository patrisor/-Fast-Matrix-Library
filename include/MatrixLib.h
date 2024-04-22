#ifndef MATRIXLIB_H
#define MATRIXLIB_H

#include <vector>
#include <string>
#include <future>

#include <iomanip>
#include <numeric>

#include <sstream>
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
        rows(init.size()), 
        cols(init.begin()->size()),
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
     * Compares two matrices for equality.
     * 
     * @param rhs The right-hand side matrix to compare with this matrix.
     * @return true if both matrices are the same size and all corresponding 
     *         elements are equal; false otherwise.
     */
    bool operator==(const Matrix<T>& rhs) const {
        return rows == rhs.rows && cols == rhs.cols && data == rhs.data;
    }

    /**
     * Compares two matrices for inequality.
     * 
     * @param rhs The right-hand side matrix to compare with this matrix.
     * @return true if the matrices are not the same size or if any 
     *         corresponding elements are different; false otherwise.
     */
    bool operator!=(const Matrix<T>& rhs) const {
        return !(*this == rhs);
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
        // Launch asynchronous tasks for each block of the resulting matrix
        int blockSize = 128;
        std::vector<std::future<void>> futures;
        for (int i = 0; i < rows; i += blockSize) {
            for (int j = 0; j < other.cols; j += blockSize) {
                futures.push_back(std::async(
                    std::launch::async,
                    &Matrix::multiplyBlock,
                    this, i, j, blockSize,
                    std::cref(other),
                    std::ref(result)
                ));
            }
        }
        // Wait for all asynchronous tasks to complete
        for (auto& future : futures)
            future.get();
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
        std::vector<std::future<void>> futures;
        for (int i = 0; i < rows; i += blockSize) {
            for (int j = 0; j < cols; j += blockSize) {
                futures.push_back(std::async(
                    std::launch::async,
                    [=, &result]() {
                        transposeBlock(i, j, blockSize, result);
                    }
                ));
            }
        }
        // Wait for all asynchronous tasks to complete
        for (auto& future : futures)
            future.get();
        return result;
    }

    /* ********************************************************************* */
    /* *************************** Visualization *************************** */
    /* ********************************************************************* */

    /**
     * Prints the matrix to standard output.
     * 
     * @param indent Number of spaces to indent before printing the matrix.
     * @param color The color code to apply to the matrix.
     */
    void print(int indent = 0, const std::string& color = "\033[0m") const {
        std::ostringstream stream;
        // Add indentation to the beginning of each line
        std::string padding(indent, ' ');
        // Calculate the maximum width required for each column
        std::vector<int> columnWidths = getColumnWidths();
        // Generate string representation of matrix
        int totalWidth = std::accumulate(
            columnWidths.begin(), 
            columnWidths.end(), 0
        ) + cols;
        const std::string resetColorCode = "\033[0m";
        stream << color << padding << "┌" << std::string(totalWidth + 1, ' ') 
               << "┐\n" << resetColorCode;
        for (int i = 0; i < rows; ++i) {
            stream << color << padding << "|";
            for (int j = 0; j < cols; ++j)
                stream << " " << std::setw(columnWidths[j]) << (*this)(i, j);
            stream << " |\n" << resetColorCode;
        }
        stream << color << padding << "└" << std::string(totalWidth + 1, ' ') 
               << "┘\n" << resetColorCode;
        // Print string representation of matrix
        std::cout << stream.str();
    }

private:
    /* ********************************************************************* */
    /* ************************** Helper Functions ************************* */
    /* ********************************************************************* */

    /**
     * Counts the number of digits in a given integer.
     * 
     * @param n The integer whose digits are to be counted.
     * @return The number of digits in the integer.
     */
    int countDigits(int n) const {
        n = std::abs(n);
        if (n == 0) return 1;
        int digits = 0;
        while (n != 0) {
            n /= 10;
            digits++;
        }
        return digits;
    }

    /**
     * Calculates the maximum width required for each matrix column.
     * 
     * @return A vector containing the maximum width for each column.
     */
    std::vector<int> getColumnWidths() const {
        std::vector<int> columnWidths(cols, 0);
        for (int j = 0; j < cols; ++j) {
            for (int i = 0; i < rows; ++i) {
                int element = (*this)(i, j);
                int width = countDigits(element);
                if (element < 0) width++; // Account for negative sign
                columnWidths[j] = std::max(columnWidths[j], width);
            }
        }
        return columnWidths;
    }

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
                for (int k = 0; k < cols; ++k)
                    sum += (*this)(i, k) * other(k, j);
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
        int blockRowEnd = std::min(row + blockSize, rows);
        int blockColEnd = std::min(col + blockSize, cols);
        for (int i = row; i < blockRowEnd; ++i) {
            for (int j = col; j < blockColEnd; ++j) {
                result(j, i) = (*this)(i, j);
            }
        }
    }
};

#endif // MATRIXLIB_H