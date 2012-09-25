CODE KATA - SORT FINITE NUMBER OF SORTED INFINITE STREAMS

This problem was presented to me recently in a job interview. As the title says, you have n infinite streams of integers sorted in ascending order. Your goal is to return a single sorted infinite stream.

My solution is to create a SortedStream class that maintains a Min Heap of Stream objects.