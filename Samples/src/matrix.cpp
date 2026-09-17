#include "matrix.hpp"
#include "../SIMD/dot_product.hpp"

#include <iostream>

Matrix::Matrix(std::size_t rows, std::size_t cols)
    : rows_(rows),
      cols_(cols),
      data_(rows * cols) // init vector with n * m elements
{
}

float& Matrix::operator()(std::size_t row, std::size_t col)
{
    return data_[row * cols_ + col];
}

const float& Matrix::operator()(std::size_t row, std::size_t col) const
{
    return data_[row * cols_ + col];
}

std::size_t Matrix::rows() const
{
    return rows_;
}

std::size_t Matrix::cols() const
{
    return cols_;
}

const float* Matrix::data() const
{
    return data_.data();
}

float* Matrix::data()
{
    return data_.data();
}

void Matrix::print_matrix(){
    for (std::size_t i = 0; i < rows_; ++i) {
        for (std::size_t j = 0; j < cols_; ++j) {
            std::cout << data_[i * cols_ + j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix multiply(const Matrix& A, const Matrix& B){
    Matrix BT(B.cols(), B.rows());
    // Transposition B
    for (std::size_t i = 0; i < B.rows(); ++i) {
        for (std::size_t j = 0; j < B.cols(); ++j) {
            BT(j, i) = B(i, j);
        }
    }

    Matrix C(A.rows(), B.cols());

    for (std::size_t row = 0; row < A.rows(); ++row) {
        const float* rowA = &A(row, 0);
        for (std::size_t column = 0; column < B.cols(); ++column) {
            const float* rowBT = &BT(column, 0);

            C(row, column) = dot_product(
                 rowA,
                 rowBT,
                 A.cols()
            );
        }
    }

    return C;
}

