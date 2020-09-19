#include <iomanip>
#include <cstring>
#include <cmath>
#include "matrix_algos.h"


// Конструктор матрицы
Matrix::Matrix(unsigned int _size) : sizeMatrix(_size)
{
    matrix = new double*[sizeMatrix];
    matrix[0] = new double[sizeMatrix * sizeMatrix];
    for(unsigned int i = 0; i < sizeMatrix; i++) {
        matrix[i] = matrix[0] + sizeMatrix * i;
        memset(matrix[i], 0, sizeMatrix);
    }
}

// Конструктор матрицы по двумерному массиву
Matrix::Matrix(double **_array, unsigned int _size) : sizeMatrix(_size)
{
    matrix = new double*[sizeMatrix];
    matrix[0] = new double[sizeMatrix * sizeMatrix];
    for(unsigned int i = 0; i < sizeMatrix; i++) {
        matrix[i] = matrix[0] + sizeMatrix * i;
        for(unsigned int j = 0; j < sizeMatrix; j++)
            matrix[i][j] = _array[i][j];
    }
}

// Деструктор матрицы
Matrix::~Matrix()
{
    delete [] matrix[0];
    delete [] matrix;
}

double **Matrix::getSubMatrix(double **_matrix, unsigned int size, unsigned int delim_x, unsigned int delim_y)
{
    unsigned int subSize = size - 1;
    double **subMatrix = new double*[subSize];
    subMatrix[0] = new double[subSize * subSize];
    for(unsigned int i = 0, h = 0; i < subSize; i++, h++) {
            subMatrix[i] = subMatrix[0] + subSize * i;
        for(unsigned int j = 0, k = 0; j < subSize; j++, k++)
            subMatrix[i][j] = _matrix[(h == delim_y) ? ++h : h][(j == delim_x) ? ++k : k];
    }
    return subMatrix;
}

// Вычисление определителя
double Matrix::procDeterm(double **_matrix, unsigned int size)
{
    if(size <= 1) {
        return _matrix[0][0];
    }
    
    double determinator = 0;
    for(unsigned int i = 0; i < size; i++) {
        double **subMatrix = getSubMatrix(_matrix, size, i, 0);
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

// Транспонирование матрицы
void Matrix::transpose()
{
    for(unsigned int i = 0; i < sizeMatrix; i++)
        for(unsigned int j = 0; j < sizeMatrix; j++)
            if(j > i) {
                double tmp = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = tmp;
            }
}

// Получение обратной матрицы
void Matrix::inverse()
{
    double determ = getDeterm();
    
    if(determ == 0)
        return;
    
    double **invMatrix = new double*[sizeMatrix];
    invMatrix[0] = new double[sizeMatrix * sizeMatrix];
    for(unsigned int i = 0; i < sizeMatrix; i++) {
        invMatrix[i] = invMatrix[0] + sizeMatrix * i;
        for(unsigned int j = 0; j < sizeMatrix; j++) {
            double **subMatrix = getSubMatrix(matrix, sizeMatrix, j, i);
            invMatrix[i][j] = procDeterm(subMatrix, sizeMatrix - 1) * 
                ((((sizeMatrix * i + j) % 2) == 1) ? -1 : 1) / determ;
            delete [] subMatrix[0];
            delete [] subMatrix;
        }
    }
    
    for(unsigned int i = 0; i < sizeMatrix; i++)
        for(unsigned int j = 0; j < sizeMatrix; j++)
            matrix[i][j] = invMatrix[i][j];
    
    delete [] invMatrix[0];
    delete [] invMatrix;
    
    transpose();
}

// Фукнция получения определителя
double Matrix::getDeterm()
{
    return procDeterm(matrix, sizeMatrix);
}

// Получение размера матрицы
unsigned char Matrix::size()
{
    return sizeMatrix;
}

// Возвращение элемента матрицы
double *Matrix::operator[](unsigned int _row)
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
