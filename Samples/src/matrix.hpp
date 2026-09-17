#pragma once

#include <cstddef>
#include <vector>

class Matrix {
public:
    Matrix(std::size_t rows, std::size_t cols);

    std::size_t rows() const;
    std::size_t cols() const;

    // const float* -- Function returns const float* - cannot modify data under pointer
    const float* data() const;
    float* data();

    // operator() allows you threat class as a function
    float& operator()(std::size_t row, std::size_t col);
    const float& operator()(std::size_t row, std::size_t col) const;

    void print_matrix();

private:
    std::size_t rows_;
    std::size_t cols_;
    std::vector<float> data_;
};

Matrix multiply(const Matrix& A, const Matrix& B);
Matrix multiply_SIMD(const Matrix& A, const Matrix& B);