#!/usr/bin/python
# -*- coding: utf-8 -*-

from grimheaper.ext import heap


class BinaryHeap(object):
    def __init__(self):
        self._heap = heap.create_heap()

    def put(self, item):
        return heap.put(self._heap, item)

    def size(self):
        return heap.size(self._heap)
