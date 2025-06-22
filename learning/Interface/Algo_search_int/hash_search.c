#include <string.h>
//哈希表大小
#define MAXKEY 1000

//哈希函数，处理数组元素返回哈希表下标
int hash(char *key) {
	int h = 0, g;
	while (*key) {
		h = (h << 4) + *key++;
		g = h & 0xf0000000;
		if (g)
			h ^= g >> 24;
		h &= ~g;
	}
	return h % MAXKEY;
}

//输入：数组地址，数组长度，查询值
//输出：找到返回查询值在数组中的下标，或-1
int hash_search(char (*pArr)[100], int len, char *target)
{
    //建立哈希表
    //如果需要多次查询，将哈希表放在主函数内, 然后用参数引进来
    int hashTable[MAXKEY] = {0};    
    //初始化哈希表，所有元素设为-1
    memset(hashTable, -1, MAXKEY * sizeof(int));
    //给哈希表赋值
    //哈希表的下标，是经过哈希函数处理过的数组元素
    //哈希表的值，是数组元素的下标
    for (int i = 0; i < len; ++i) {
        hashTable[hash(pArr[i])] = i;
    }

    return hashTable[hash(target)];
}

