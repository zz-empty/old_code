void insert_sort(int *arr, int len)
{
    //手牌从1到N, 牌堆从N-1到0，遍历牌堆插入手牌
    //i 表示牌堆
    for (int i = 1; i < len; ++i) {
        //保存来牌
        int val = arr[i];
        //在手牌中从后往前给来牌腾位置
        int j = i - 1;  //手牌最后一位的下标
        for (; j >= 0; --j) {
            if (arr[j] > val) {
                arr[j + 1] = arr[j];
            }
            else {
                break;
            }
        }
        //插入来牌
        arr[j + 1] = val;
    }
}
