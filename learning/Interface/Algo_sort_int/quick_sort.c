int partition(int *arr, int left, int right)
{
    //选数组最后一个元素作为枢纽
    //i 用来遍历数组
    //j 是一个界限，左边元素都比分割器小
    int pivot = arr[right];
    int i = left;
    int j = left;
    for (; i < right; ++i) {
        if (arr[i] < pivot) {
            //比枢纽小的，放j左边
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;

            ++j;
        }
    }

    //将枢纽放中间
    arr[right] = arr[j];
    arr[j] = pivot;

    //返回枢纽的下标
    return j;
}

void quick_sort(int *arr, int left, int right) //left:首元素下标，right:尾元素下标
{
    if (right > left) {     //数组范围大于1，就进入递归
        int pivot = partition(arr, left, right);    //通过划分得到枢纽
        quick_sort(arr, left, pivot - 1);       //递归枢纽左半边
        quick_sort(arr, pivot + 1, right);      //递归枢纽右半边
    }
}
