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

long **Matrix::getSubMatrix(long **_matrix, unsigned int size, unsigned int delim_x, unsigned int delim_y)
{
    unsigned int subSize = size - 1;
    long **subMatrix = new long*[subSize];
    subMatrix[0] = new long[subSize * subSize];
    for(unsigned int i = 0, h = 0; i < subSize; i++, h++) {
            subMatrix[i] = subMatrix[0] + subSize * i;
        for(unsigned int j = 0, k = 0; j < subSize; j++, k++)
            subMatrix[i][j] = _matrix[(h == delim_y) ? ++h : h][(j == delim_x) ? ++k : k];
    }
    return subMatrix;
}

// Вычисление определителя
long long Matrix::procDeterm(long **_matrix, unsigned int size)
{
    if(size <= 1) {
        return _matrix[0][0];
    }
    
    long long determinator = 0;
    for(unsigned int i = 0; i < size; i++) {
        long **subMatrix = getSubMatrix(_matrix, size, i, 0);
        determinator += _matrix[0][i] * procDeterm(subMatrix, size - 1) * ((i % 2 == 0) ? 1 : -1);
        delete [] subMatrix[0];
        delete [] subMatrix;
    }
    
    return determinator;
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
void Matrix::random(const long range, unsigned int _rand)
{
    srand(_rand);
    for(unsigned int i = 0; i < sizeMatrix; i++)
        for(unsigned int j = 0; j < sizeMatrix; j++)
            matrix[i][j] = rand() % range;
}

// Поменять строки и столбцы матрицы местами
void Matrix::replace()
{
    for(unsigned int i = 0; i < sizeMatrix; i++)
        for(unsigned int j = 0; j < sizeMatrix; j++) {
            long tmp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = tmp;
        }
}

// Фукнция получения определителя
long long Matrix::getDeterm()
{
    return procDeterm(matrix, sizeMatrix);
}

// Получение размера матрицы
unsigned char Matrix::size()
{
    return sizeMatrix;
}

// Возвращение элемента матрицы
long *Matrix::operator[](unsigned int _row)
{
    if(0 <= _row || _row < sizeMatrix)
        return matrix[_row];
    return nullptr;
}

// Перегрузка оператора потокового вывода
std::ostream &operator<<(std::ostream &out, Matrix matrix)
{
    for(unsigned int i = 0; i < matrix.size(); i++) {
        for(unsigned int j = 0; j < matrix.size(); j++)
            out << std::setw(5) << matrix[i][j] << ' ';
        out << std::endl;
    }
    return out;
}
