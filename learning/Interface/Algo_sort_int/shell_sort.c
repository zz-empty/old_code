void shell_sort(int *arr, int len)
{
    for (int gap = len >> 1; gap > 0; gap >>= 1) {
        for (int i = gap; i < len; ++i) {
            //保存来牌
            int val = arr[i];
            //在手牌中从后往前给来牌腾位置
            int j = i - gap;
            for (; j >= 0; j -= gap) {
                if (arr[j] > val) {
                    arr[j + gap] = arr[j];
                }
                else {
                    break;
                }
            }
            //插入来牌
            arr[j + gap] = val;
        }
    }
}
