/**
 * @file Matrix.hpp
 * @author Habib Moukalled
 * @email habib.moukalled@gmail.com
 *
 * @brief This template class implements a matrix class
 * for any desired data type.
 *
 * @date 01/12/2019
 */

#include <iostream>
#include <cstdint>
#include <valarray>
#include <limits>

template <typename T>
class Matrix {
    private:
        size_t m_rows; ///< The height of the matrix.
        size_t m_cols; ///< The width of the matrix.
        size_t m_numBins; ///< The number of histogram bins.
        std::valarray<T> m_data; ///< The array where the matrix's data payload is stored.
        std::valarray<T> m_histogram; ///< The array where the histogram payload will be stored.
        std::valarray<T> m_binValues; ///< The array where the histogram values payload will be stored.

    public:
        // For safety reasons we define two types of constructors.
        // one that takes no arguments, and one that takes
        // the size of the matrix in rows and columns. In
        // both constructors, member variables are initialized
        // using a constructor initializer list.

        ///< Default constructor defaults to a 2x2 matrix, when
        ///< no user specified dimensions are given.
        Matrix() :  m_rows(2),
                    m_cols(2),
                    m_numBins(0),
                    m_data(rows * cols) {

        }

        ///< Method constructs a matrix based on user defined size.
        Matrix(const size_t rows, const size_t cols) :
                                                        m_rows(rows),
                                                        m_cols(cols), 
                                                        m_numBins(0),
                                                        m_data(rows * cols) {

        }

        ///< Accessor method used to retun the height of the matrix.
        const size_t rows() { return m_rows; }

        ///< Accessor method use to return the width of the matrix.
        const size_t cols() { return m_cols; }

        ///< Mutator method used to adjust height of matrix.
        void rows(const size_t rows) { m_rows = rows; }

        ///< Mutator method used to adjust the width of the matrix.
        void cols(const size_t cols) { m_cols = cols; }
        
        ///< This overloaded () operator is used to return
        ///< The value of the matrix at (row, col).
        T operator()(const size_t row, const size_t col) const {
            // It only makes sense to acces the (i, j)th matrix
            // entry if it exists. Note, in writing a more robust library,
            // exceptions would be thrown for element out of bounds.
            if (row >= 0 && row <= m_rows &&
                    col >= 0 && col <= m_cols) {

                return m_data[row * m_cols + col];
            }
            else {
                std::cout << "Matrix::() operator Error: accessing (" << row << ", " << col << "), element out of bounds!" <<
                    std::endl;
            }
        }

        ///< This overloaded () operator is used to return
        ///< a reference to the matrix data at (row, col).
        T &operator()(const size_t row, const size_t col) {
            // It only makes sense to acces the (i, j)th matrix
            // entry if it exists. Note, in writing a more robust library,
            // exceptions would be thrown for element out of bounds.
            if (row >= 0 && row <= m_rows &&
                    col >= 0 && col <= m_cols) {

                return m_data[row * m_cols + col];
            }
            else {
                std::cout << "Matrix::() operator Error: accessing (" << row << ", " << col << "), element out of bounds!" <<
                    std::endl;
            }
        }
        ///< This is an overloaded assignment operator.
        ///< It doubles as a copy operator.
        Matrix& operator=(Matrix& rhs) {
            m_rows = rhs.rows();
            m_cols = rhs.cols();
            m_data = rhs.data();

            return *this;
        }

        std::valarray<T> data() {
            return m_data;
        }

        ///< A function to print the contents of the Matrix.
        void print(const char* matrixName = "defaultName") {
            std::cout << "Matrix::print(): Matrix " << matrixName << ": " << std::endl;

            for (size_t i = 0; i < m_rows; ++i) {
                for (size_t j = 0; j < m_cols; ++j) {
                    if (j < m_cols - 1) {
                        std::cout << m_data[i * m_cols + j] << ", ";
                    }
                    else {
                        std::cout << m_data[i * m_cols + j] << std::endl;
                    }
                }
            }

            std::cout << "Matrix::print(): End of Matrix " << matrixName << "\n" << std::endl;
        }

        ///< The histogram() function will retun an array
        ///< containing the intensity values per bin.
        std::valarray<T> histogram(const size_t numBins) {
            // It only makes sense to perform the histogram
            // operation if we have at least one bin. Again
            // in more mission ctritical code, exceptions should
            // be thrown.
            if (numBins > 0) {
                m_numBins = numBins;
                m_histogram.resize(numBins);
                m_binValues.resize(numBins);
                const T minVal = 0;
                const T maxVal = std::numeric_limits<T>::max();

                // (1.) Compute the range of intensity values
                // for each bin.
                const size_t numElements = m_rows * m_cols;
                const size_t rangePerBin = maxVal / m_numBins;

                T val = 0;
                for (size_t i = 0; i < m_numBins; ++i) {
                    val += rangePerBin;
                    m_binValues[i] = val;
                    std::cout << "Matrix::histogram(): binValues(" << i << ") = " << (int) m_binValues[i] << std::endl;
                }

                // (2.) Using the bin values, start counting the
                // number of intensity values that fall within the
                // range specified by each bin.
                for (size_t i = 0; i < numElements; ++i) {
                    for (size_t j = 0; j < m_numBins; ++j) {
                        if (j > 0) {
                            if (m_data[i] >= m_binValues[j - 1] && m_data[i] <= m_binValues[j]) {
                                m_histogram[j]++;
                            }
                        }
                        else {
                            if (m_data[i] >= 0 && m_data[i] <= m_binValues[j]) {
                                m_histogram[j]++;
                            }
                        }
                    }
                }
                std::cout << " " << std::endl;
                for (size_t i = 0; i < m_numBins; ++i) {
                    std::cout << "Matrix::histogram(): histogram(" << i << ") = " << (int) m_histogram[i] << std::endl;
                }
            }

            return m_histogram;
        }

        const size_t bins() { return m_numBins; }

        std::valarray<T> binValues() {
            if (m_numBins > 0) {
                return m_binValues;
            }
            else {
                return NULL;
            }
        }
};
