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
    unsigned int sizeMatrix;
public:
    // Конструктор матрицы
    Matrix(unsigned int _size = 3);
    // Деструктор матрицы
    ~Matrix();
    // Фукнция получения определителя
    long getDeterm();
    // Вывод матрицы
    void print(unsigned int _t = 5);
    // Ввод матрицы
    void scan();
    // Заполнение матрицы случайными числами
    void randMatrix(const long range = 1000);
    // Поменять строки и столбцы матрицы местами
    void replace();
    // Возвращение элемента матрицы
    long *operator[](unsigned int _row);
};

#endif
