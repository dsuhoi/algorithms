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

