#!/usr/bin/python
# -*- coding: utf-8 -*-

import unittest

from grimheaper.heap import BinaryHeap


class TestHeap(unittest.TestCase):

    def setUp(self):
        self.heap = BinaryHeap()

    def test_is_heap(self):
        self.assertIsInstance(self.heap, BinaryHeap)

    #def test_put(self):
        #for i in range(5):
            #self.heap.put(i + 1)

        #self.assertEqual(self.heap.pop(), 5)
        #self.assertEqual(self.heap.pop(), 4)
        #self.assertEqual(self.heap.pop(), 3)
        #self.assertEqual(self.heap.pop(), 2)
        #self.assertEqual(self.heap.pop(), 1)
