#!/usr/bin/python
# -*- coding: utf-8 -*-

from grimheaper.ext import heap


class BinaryHeap(object):
    def __init__(self):
        heap.create_heap()

    def put(self, item):
        heap.put(item)
