#include <iostream>
#include <iomanip>
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
void Matrix::print(int _t)
{    
    for(size_t i = 0; i < sizeMatrix; i++) {
        for(size_t j = 0; j < sizeMatrix; j++)
            std::cout << std::setw(_t) << matrix[i][j] << ' ';
        std::cout << std::endl;
    }
}

// Ввод матрицы
void Matrix::scan()
{
    for(size_t i = 0; i < sizeMatrix; i++) {
        for(size_t j = 0; j < sizeMatrix; j++) {
            std::cout << "Enter the value [" << i << "][" << j << "] element: ";
            std::cin >> matrix[i][j];
        }
        std::cout << std::endl;
    }
}

// Возвращение элемента матрицы
long &Matrix::operator()(size_t _row, size_t _column)
{
    if((0 <= _row || _row < sizeMatrix) && (0 <= _column || _column < sizeMatrix))
        return matrix[_row][_column];
}
