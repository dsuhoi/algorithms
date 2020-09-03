/*
 * matrix_algos.h
 * 
 * Библиотека по работе с квадратными матрицами
 * (C++)
 */

#ifndef __MATRIX_H__
#define __MATRIX_H__

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
    void print();
    // Ввод матрицы
    void scan();
    // Возвращение элемента матрицы
    long getMatrix(size_t);
};

#endif
