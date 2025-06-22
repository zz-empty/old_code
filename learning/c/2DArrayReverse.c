#include <stdio.h>

#define N 3
#define SWAP(a, b) {int tmp = a; a = b; b = tmp;}

void reverse2DArray(int arr[][N], int len) {
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < i; j++) {
            SWAP(arr[i][j], arr[j][i]);
        }
    }
  
}

void print2DArray(int arr[][N], int len) {
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < N; j++) {
            printf("%-3d", arr[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int arr[][N] = {{1, 2, 3}, {9, 8, 7}, {4, 9, 72}};
    print2DArray(arr, 3);
    reverse2DArray(arr, 3);
    print2DArray(arr, 3);

    return 0;
}

