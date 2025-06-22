#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *find_common(int *nums1, int size_1, int *nums2, int size_2, int *result_size) {
    int maxsize = size_1 < size_2 ? size_1 : size_2;
    int *result = (int*)malloc(maxsize * sizeof(int));
    memset(result, 0, sizeof(int) * maxsize);

    int i = 0, j = 0, k = 0;
    while (i < size_1 && j < size_2) {
        if (nums1[i] < nums2[j]) {
            ++i;
        } else if (nums1[i] > nums2[j]) {
            ++j;
        } else {
            result[k++] = nums1[i];
            ++i;
            ++j;
        }
    }
    *result_size = k;

    return result;
}

void print_arr(int *arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%-3d", arr[i]);
    }
    printf("\n");
}

int main()
{
    int a[] = {1, 2, 3, 4, 9, 12, 13, 18, 29, 45};
    int b[] = {2, 4, 6, 7, 9, 29};

    int size_a = sizeof(a) / sizeof (a[0]);
    int size_b = sizeof(b) / sizeof (b[0]);
    printf("a:");
    print_arr(a, size_a);
    printf("b:");
    print_arr(b, size_b);


    int len = 0;
    int *res = find_common(a, size_a, b, size_b, &len);
    print_arr(res, len);

    free(res);
    return 0;
}

