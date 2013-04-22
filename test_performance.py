#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import time

from grimheaper.heap import BinaryHeap


def main():
    args = sys.argv[1:]
    passes = 100000
    if args:
        passes = int(args[0])

    heap = BinaryHeap()

    print "Creating heap with %d items..." % passes
    started = time.time()
    for i in range(passes):
        heap.put(i)

    print "Heap filled with %d items after %.2fms" % (passes, time.time() - started)

if __name__ == '__main__':
    main()
