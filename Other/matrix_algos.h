/*
 * matrix_algos.h
 * 
 * Библиотека по работе с квадратными матрицами
 * (C++)
 */

#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <iostream>


class Matrix {
private:
    // Указатель на элементы матрицы
    long **matrix;
    // Размерность матрицы
    size_t sizeMatrix;
public:
    // Конструктор матрицы по умолчанию
    Matrix();
    // Конструктор матрицы с параметром
    Matrix(size_t _size);
    // Деструктор матрицы
    ~Matrix();
    // Фукнция получения определителя
    long getDeterm();
    // Вывод матрицы
    void print();
    // Ввод матрицы
    void scan();
    // Возвращение элемента матрицы
    long getMatrix(size_t)
};

