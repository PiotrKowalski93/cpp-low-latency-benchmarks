#include "matrix.hpp"

#include <iostream>

int main()
{
    std::cout << "Matrix multiply: " << std::endl;

    Matrix A(2, 3);
    Matrix B(3, 2);

    A(0, 0) = 1;
    A(0, 1) = 2;
    A(0, 2) = 3;

    A(1, 0) = 4;
    A(1, 1) = 5;
    A(1, 2) = 6;

    B(0, 0) = 7;
    B(0, 1) = 8;

    B(1, 0) = 9;
    B(1, 1) = 10;

    B(2, 0) = 11;
    B(2, 1) = 12;

    std::cout << "A: " << std::endl;
    A.print_matrix();

    std::cout << "B: " << std::endl;
    B.print_matrix();

    Matrix C = multiply(A, B);
    std::cout << "C: " << std::endl;
    C.print_matrix();
}
