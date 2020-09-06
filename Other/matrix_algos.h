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
    
    // Вычисление подматрицы
    long **getSubMatrix(long **_matrix, unsigned int size, unsigned int delim);
    // Вычисление определителя
    long long procDeterm(long **_matrix, unsigned int size);
public:
    // Конструктор матрицы
    Matrix(unsigned int _size = 3);
    // Деструктор матрицы
    ~Matrix();
    // Фукнция получения определителя
    long long getDeterm();
    // Получение размера матрицы
    unsigned char size();
    // Вывод матрицы
    void print(unsigned int _t = 5);
    // Ввод матрицы
    void scan();
    // Заполнение матрицы случайными числами
    void random(const long range = 1000);
    // Поменять строки и столбцы матрицы местами
    void replace();
    // Возвращение строки матрицы
    long *operator[](unsigned int _row);
    // Перегрузка оператора сложения
    Matrix operator+(Matrix &matrix);
    // Перегрузка оператора вычитания
    Matrix operator-(Matrix &matrix);
    // Перегрузка оператора потокового вывода
    friend std::ostream &operator<<(std::ostream &out, Matrix &matrix);
};

#endif
