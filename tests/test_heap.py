#!/usr/bin/python
# -*- coding: utf-8 -*-

import unittest

from grimheaper.heap import BinaryHeap


class TestHeap(unittest.TestCase):

    def setUp(self):
        self.heap = BinaryHeap()

    def test_is_heap(self):
        self.assertIsInstance(self.heap, BinaryHeap)
        self.assertIsInstance(self.heap.items, list)
        self.assertEqual(len(self.heap.items), 1)
        self.assertEqual(self.heap.items[0], None)

    def test_put(self):
        self.heap.put(5)
        self.assertEqual(len(self.heap.items), 2)

    def test_many_puts(self):
        for i in range(8):
            self.heap.put(i + 1)

        self.assertEqual([None, 8, 7, 6, 4, 3, 2, 5, 1], self.heap.items)

    #def test_put_other(self):
        #item = self.heap.put(2)
        #item = self.heap.put(3)
        #self.assertEqual(1, item)

        #item = self.heap.put(3)
        #self.assertEqual(item, 1)

        #item = self.heap.put(1)
        #self.assertEqual(item, 3)
