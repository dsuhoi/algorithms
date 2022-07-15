#include <stdio.h>
#include <stdlib.h>

void print_arr(int *arr, const int n, const int m, const int z)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            for (int k = 0; k < z; k++)
                printf("%3d ", arr[z * m * i + z * j + k]);
            putchar('\n');
        }
        puts("\n");
    }
}

int ***init_arr3(size_t n, size_t m, size_t z)
{
    int ***arr = malloc(n * sizeof(int **) + n * m * sizeof(int *) +
                        n * m * z * sizeof(int));
    arr[0] = (int **)(arr + n);
    arr[0][0] = (int *)(arr[0] + n * m);
    for (int i = 0; i < n; i++)
    {
        arr[i] = arr[0] + m * i;
        for (int j = 0; j < m; j++)
        {
            arr[i][j] = arr[0][0] + z * (m * i + j);
            for (int k = 0; k < z; k++) arr[i][j][k] = 0;
        }
    }

    return arr;
}

int main(void)
{
    const int N = 2, M = 4, K = 5;

    int ***arr = init_arr3(N, M, K);

    print_arr(arr[0][0], N, M, K);

    free(arr);
    return 0;
}
