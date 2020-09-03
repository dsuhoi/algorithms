#include <iostream>
#include <iomanip>
#include <cstring>
#include "matrix_algos.h"


// Конструктор матрицы
Matrix::Matrix(unsigned int _size) : sizeMatrix(_size)
{
    matrix = new long*[sizeMatrix];
    matrix[0] = new long[sizeMatrix * sizeMatrix];
    for(unsigned int i = 0; i < sizeMatrix; i++) {
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
void Matrix::print(unsigned int _t)
{    
    for(unsigned int i = 0; i < sizeMatrix; i++) {
        for(unsigned int j = 0; j < sizeMatrix; j++)
            std::cout << std::setw(_t) << matrix[i][j] << ' ';
        std::cout << std::endl;
    }
}

// Ввод матрицы
void Matrix::scan()
{
    for(unsigned int i = 0; i < sizeMatrix; i++) {
        for(unsigned int j = 0; j < sizeMatrix; j++) {
            std::cout << "Enter the value [" << i << "][" << j << "] element: ";
            std::cin >> matrix[i][j];
        }
        std::cout << std::endl;
    }
}

// Заполнение матрицы случайными числами
void Matrix::randMatrix(const long range)
{
    srand(time(NULL));
    for(unsigned int i = 0; i < sizeMatrix; i++)
        for(unsigned int j = 0; j < sizeMatrix; j++)
            matrix[i][j] = rand() % range;
}

// Возвращение элемента матрицы
long *Matrix::operator[](unsigned int _row)
{
    if(0 <= _row || _row < sizeMatrix)
        return matrix[_row];
    return nullptr;
}
