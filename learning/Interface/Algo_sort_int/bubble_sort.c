
//传入数组地址，数组长度
void bubble_sort(int *arr, int len)
{
    //排序
    //i 表示查找的范围
    //j 表示冒泡的起始位置
    for (int i = len; i > 1; --i) {
        for (int j = 0; j < i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                //比后一个元素大，交换值
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

//传入数组首尾地址
void bubble_sort2(int *begin, int *end)
{
    int len = 0;
    int *start = begin;
    for (; start != end; ++start) {
        ++len;
    }
    
    //排序
    //i 表示查找的范围
    //j 表示冒泡的起始位置
    for (int i = len; i > 1; --i) {
        for (int j = 0; j < i - 1; ++j) {
            if (begin[j] > begin[j + 1]) {
                //比后一个元素大，交换值
                int tmp = begin[j];
                begin[j] = begin[j + 1];
                begin[j + 1] = tmp;
            }
        }
    }
}
