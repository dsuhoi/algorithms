/*
 * matrix_algos.h
 * 
 * Библиотека по работе с квадратными матрицами
 * (C++)
 */

#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <iostream>

class Matrix {
private:
    // Указатель на элементы матрицы
    long **matrix;
    // Размерность матрицы
    size_t sizeMatrix;
public:
    // Конструктор матрицы
    Matrix(size_t _size = 3);
    // Деструктор матрицы
    ~Matrix();
    // Фукнция получения определителя
    long getDeterm();
    // Вывод матрицы
    void print(int _t = 5);
    // Ввод матрицы
    void scan();
    // Возвращение элемента матрицы
    long &operator()(size_t _row, size_t column);
};

#endif
