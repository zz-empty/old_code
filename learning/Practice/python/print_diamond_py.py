#!/usr/bin/env python
# coding=utf-8

def print_diamond(n):
    for i in range(1, n + 1):
        print(' ' * (n - i) + ' '.join('*' * i))
    for i in range(n - 1, 0, -1):
        print(' ' * (n - i) + ' '.join('*' * i))

print_diamond(5);
