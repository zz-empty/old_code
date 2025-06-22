#ifndef __LRUCACHE_HPP__
#define __LRUCACHE_HPP__


#include <iostream>
#include <unordered_map>
#include <list>

using std::cout;
using std::endl;
using std::unordered_map;
using std::list;
using std::pair;

namespace LRU
{

template <typename K, typename V>
class LRUCache
{
public:
    LRUCache(size_t capacity) : _capacity(capacity)
    {}

    //获取键对应的值，如果不存在则返回-1
    int get(int key)
    {
        if (_cacheMap.find(key) == _cacheMap.end()) {
            return -1;  //缓存未命中
        }

        //缓存命中，将节点移至链表末尾表示最近访问
        _cacheList.splice(_cacheList.end(), _cacheList, _cacheMap[key]);
        return _cacheMap[key]->second;
    }

    //设置或更新键对应的值
    void put(int key, int value)
    {
        if (_cacheMap.find(key) != _cacheMap.end()) {
            //如果键存在，则更新值，并将节点移到链表末尾
            _cacheMap[key]->second = value;
            _cacheList.splice(_cacheList.end(), _cacheList, _cacheMap[key]);
        } else {
            //如果键不存在，则创建新节点
            if (_cacheList.size() == _capacity) {
                //如果缓存已满，则移除最久未使用的节点（链表头部）
                auto it = _cacheList.begin();
                _cacheMap.erase(it->first);
                _cacheList.erase(it);
            }

            //插入新节点到链表末尾，并在哈希表中添加映射
            _cacheList.emplace_back(key, value);
            _cacheMap[key] = --_cacheList.end();
        }
    }
private:
    unordered_map<K, typename list<pair<K, V>>::iterator> _cacheMap; 
    list<pair<K, V>> _cacheList;
    size_t _capacity;
};

}// end of namespace LRU

#endif
