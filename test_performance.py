#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import time

from grimheaper.heap import BinaryHeap
from Queue import PriorityQueue


def main():
    args = sys.argv[1:]
    passes = 1000000
    if args:
        passes = int(args[0])

    print
    print "Using GrimHeaper..."
    print

    heap = BinaryHeap()

    print
    print "Creating heap with %d items..." % passes
    print

    started = time.time()
    for i in range(passes):
        heap.put(i)

    fill_time = time.time() - started
    print
    print "Heap filled with %d items after %.2fms" % (passes, fill_time)

    started = time.time()
    for i in range(passes):
        heap.pop()

    empty_time = time.time() - started
    print "Heap emptied with %d items after %.2fms" % (passes, empty_time)
    print
    print "Total time: %.2f" % (fill_time + empty_time)

    print
    print "Using Python's PriorityQueue..."
    print

    queue = PriorityQueue()

    print
    print "Creating queue with %d items..." % passes
    print

    started = time.time()
    for i in range(passes):
        queue.put(i)

    fill_time = time.time() - started
    print
    print "Queue filled with %d items after %.2fms" % (passes, fill_time)

    started = time.time()
    for i in range(passes):
        queue.get_nowait()

    empty_time = time.time() - started
    print "Queue emptied with %d items after %.2fms" % (passes, empty_time)
    print
    print "Total time: %.2f" % (fill_time + empty_time)


if __name__ == '__main__':
    main()
