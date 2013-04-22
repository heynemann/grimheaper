#!/usr/bin/python
# -*- coding: utf-8 -*-

import unittest

from grimheaper.heap import BinaryHeap


class TestHeap(unittest.TestCase):

    def setUp(self):
        self.heap = BinaryHeap()

    #def test_is_heap(self):
        #self.assertIsInstance(self.heap, BinaryHeap)
        #self.assertIsInstance(self.heap.items, list)
        #self.assertEqual(len(self.heap.items), 1)
        #self.assertEqual(self.heap.items[0], None)

    #def test_put(self):
        #self.heap.put(5)
        #self.assertEqual(len(self.heap.items), 2)

    #def test_many_puts(self):
        #for i in range(8):
            #self.heap.put(i + 1)

        #self.assertEqual([None, 8, 7, 6, 4, 3, 2, 5, 1], self.heap.items)

    #def test_odd_puts(self):
        #for i in range(9):
            #self.heap.put(i + 1)

        #self.assertEqual([None, 9, 8, 6, 7, 3, 2, 5, 1, 4], self.heap.items)

    def test_lots_of_puts(self):
        for i in range(10000):
            self.heap.put(i + 1)

        self.assertEqual(len(self.heap), 10000)

    #def test_pop(self):
        #for i in range(8):
            #self.heap.put(i + 1)

        #self.assertEqual([None, 8, 7, 6, 4, 3, 2, 5, 1], self.heap.items)

        #item = self.heap.pop()
        #self.assertEqual(len(self.heap.items), 8)
        #self.assertEqual(item, 8)
        #self.assertEqual([None, 7, 4, 6, 1, 3, 2, 5], self.heap.items)

        #item = self.heap.pop()
        #self.assertEqual(len(self.heap.items), 7)
        #self.assertEqual(item, 7)
        #self.assertEqual([None, 6, 4, 5, 1, 3, 2], self.heap.items)

        #item = self.heap.pop()
        #self.assertEqual(len(self.heap.items), 6)
        #self.assertEqual(item, 6)
        #self.assertEqual([None, 5, 4, 2, 1, 3], self.heap.items)

        #item = self.heap.pop()
        #self.assertEqual(len(self.heap.items), 5)
        #self.assertEqual(item, 5)
        #self.assertEqual([None, 4, 3, 2, 1], self.heap.items)

        #item = self.heap.pop()
        #self.assertEqual(len(self.heap.items), 4)
        #self.assertEqual(item, 4)
        #self.assertEqual([None, 3, 1, 2], self.heap.items)

        #item = self.heap.pop()
        #self.assertEqual(len(self.heap.items), 3)
        #self.assertEqual(item, 3)
        #self.assertEqual([None, 2, 1], self.heap.items)

        #item = self.heap.pop()
        #self.assertEqual(len(self.heap.items), 2)
        #self.assertEqual(item, 2)
        #self.assertEqual([None, 1], self.heap.items)

        #item = self.heap.pop()
        #self.assertEqual(len(self.heap.items), 1)
        #self.assertEqual(item, 1)
        #self.assertEqual([None], self.heap.items)

    #def test_len(self):
        #for i in range(10):
            #self.heap.put(i + 1)

        #self.assertEqual(len(self.heap), 10)
