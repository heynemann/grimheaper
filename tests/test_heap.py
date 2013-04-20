#!/usr/bin/python
# -*- coding: utf-8 -*-

import unittest

from grimheaper.heap import BinaryHeap


class TestHeap(unittest.TestCase):

    def setUp(self):
        self.heap = BinaryHeap()

    def test_is_heap(self):
        self.assertIsInstance(self.heap, BinaryHeap)

    def test_put(self):
        item = self.heap.put(5)
        self.assertEqual(item, 1)
        item = self.heap.put(4)
        self.assertEqual(item, 2)
        item = self.heap.put(3)
        self.assertEqual(item, 3)

    #def test_put_other(self):
        #item = self.heap.put(2)
        #item = self.heap.put(3)
        #self.assertEqual(1, item)

        #item = self.heap.put(3)
        #self.assertEqual(item, 1)

        #item = self.heap.put(1)
        #self.assertEqual(item, 3)
