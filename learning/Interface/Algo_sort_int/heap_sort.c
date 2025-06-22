//如果换成字符串类型的数组，那么除了修改元素类型外，涉及到比较操作和交换操作的地方，全部都要改成字符串形式的
//如果不是字符串类型的，只需修改类型即可

void adjust_maxheap(int *arr, int pos, int len)
{
    //根据根的位置，求出子节点的下标
    int dad = pos;
    int son = 2 * pos + 1;

    while (son < len) {
        if (son + 1 < len && arr[son + 1] > arr[son]) {
            //如果右孩子存在，且大于左孩子，更新孩子节点
            son = son + 1;
        }

        if (arr[son] > arr[dad]) {
            //如果子节点大于父节点，交换父子节点
            int tmp = arr[son];
            arr[son] = arr[dad];
            arr[dad] = tmp;

            //更新父子节点，向下循环，调整堆
            dad = son;
            son = 2 * dad + 1;
        }
        else {
            //父节点大于子节点，符合大根堆，退出
            break;
        }
    }
}

void heap_sort(int *arr, int len)
{
    if (2 > len) {
        return;
    }

    //从最后一个父节点开始，建立大根堆，直到首节点
    for (int i = len / 2 - 1; i >= 0; --i) {
        adjust_maxheap(arr, i, len);
    }

    //堆顶放最后
    int tmp = arr[0];
    arr[0] = arr[len - 1];
    arr[len - 1] = tmp;

    //不断缩减堆的规模，重建堆，找出当前规模的最大值
    for (int size = len - 1; size >= 1; --size) {
        adjust_maxheap(arr, 0, size);
        //建好大根堆后，堆顶放最后
        int tmp = arr[0];
        arr[0] = arr[size - 1];
        arr[size - 1] = tmp;
    }
}
