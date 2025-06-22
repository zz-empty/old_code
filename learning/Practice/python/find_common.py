#!/usr/bin/env python
import os


# coding=utf-8
def find_common(nums1, nums2):
    result = []
    i = j = 0

    while i < len(nums1) and j < len(nums2):
        if nums1[i] < nums2[j]:
            i += 1
        elif nums1[i] > nums2[j]:
            j += 1
        else:
            result.append(nums1[i])
            i += 1
            j += 1

    return result


if __name__ == "__main__":
    a = [1, 2, 2, 4, 5]
    b = [1, 2, 4, 5]

    print("公共元素：", find_common(a, b))
