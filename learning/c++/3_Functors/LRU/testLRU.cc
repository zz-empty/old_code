#include "LRUCache.hpp"
#include <iostream>

using std::cout;
using std::endl;
using namespace LRU;

void test0()
{
    LRUCache<int, int> cache(3); // 容量为3  
  
    cache.put(1, 1);  
    cache.put(2, 2);  
    cache.put(3, 3);  
  
    std::cout << "Get 1: " << cache.get(1) << std::endl; // 返回 1  
  
    cache.put(4, 4); // 移除键为2的  
    std::cout << "Get 2: " << cache.get(2) << std::endl; // 返回 -1 (未找到)  
  
    cache.put(1, 10); // 更新键为1的值  
    std::cout << "Get 1: " << cache.get(1) << std::endl; // 返回 10 

}

int main()
{
    test0();
    return 0;
}

