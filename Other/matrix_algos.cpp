#include <iostream>
#include <cstring>
#include "matrix_algos.h"


// Конструктор матрицы
Matrix::Matrix(size_t _size) : sizeMatrix(_size)
{
    matrix = new long*[sizeMatrix];
    matrix[0] = new long[sizeMatrix * sizeMatrix];
    for(size_t i = 0; i < sizeMatrix; i++) {
        matrix[i] = matrix[0] + sizeMatrix * i;
        memset(matrix[i], 0, sizeMatrix);
    }
}

// Деструктор матрицы
Matrix::~Matrix()
{
    delete [] matrix[0];
    delete [] matrix;
}


// Вывод матрицы
void Matrix::print()
{
    for(size_t i = 0; i < sizeMatrix; i++) {
        for(size_t j = 0; j < sizeMatrix; j++)
            std::cout << matrix[i][j] << ' ';
        std::cout << std::endl;
    }
}
