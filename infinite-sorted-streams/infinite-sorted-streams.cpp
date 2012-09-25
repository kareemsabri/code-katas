#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

#define NUM_STREAMS 100

/* minimal increasing integer stream class for testing */
class Stream {
    int current;
public:
    Stream() { srand(time(NULL)); current = (rand() % 100) + 1; };
    int read() { return current; };
    int next() { int temp = current; current += ((rand() % 100) + 1); assert(current > temp); return temp; };
};

/* min heap of streams - implementation ignores things like empty heap, memory allocation failure, overflowing heap etc. */
class StreamMinHeap {
    Stream *streamArray;
    int n;
public:    
    StreamMinHeap(int size);
    void add(Stream theStream);
    int removeMin();
    void print();
private:    
    void siftUp(int index);
    void siftDown(int index);
    void swap(int a, int b);
};

StreamMinHeap::StreamMinHeap(int size) {
    streamArray = (Stream *)malloc(size*sizeof(Stream));
    n = 0;
}

void StreamMinHeap::add(Stream theStream) {
    streamArray[n] = theStream;
    siftUp(n++);
}

int StreamMinHeap::removeMin() {
    /*  unlike traditional heap this just reads an int from the stream at the top of the heap
        doesn't actually remove the stream (assumed infinite)
    */
    int min = streamArray[0].next();
    if (streamArray[0].read() > streamArray[1].read() || streamArray[0].read() > streamArray[2].read()) {
        //min has shifted, re-order heap
        Stream tmp = streamArray[0];
        streamArray[0] = streamArray[n - 1];
        if (--n > 0) {
            siftDown(0);
        }
        add(tmp);
    }
    return min;
}

void StreamMinHeap::siftUp(int index) {
    if (index > 0) {
        int parent = (index - 1) >> 1;
        if (streamArray[parent].read() > streamArray[index].read()) {
            swap(parent, index);
            siftUp(parent);
        }
    }
}

void StreamMinHeap::siftDown(int index) {
    int left = (index << 1) + 1;
    int right = (index << 1) + 2;

    if (right >= n && left >= n) return;

    int smallest = streamArray[left].read() < streamArray[right].read() ? left : right;

    if (streamArray[index].read() > streamArray[smallest].read()) {
        swap(smallest, index);
        siftDown(smallest);
    }
}

void StreamMinHeap::swap(int a, int b) {
    Stream tmp = streamArray[a];
    streamArray[a] = streamArray[b];
    streamArray[b] = tmp;
}

class SortedStream {
    StreamMinHeap *heap;
public:
    SortedStream(Stream *, int);
    int next();
};

SortedStream::SortedStream(Stream *streams, int numberOfStreams) {
    heap = new StreamMinHeap(numberOfStreams);
    for(int i = 0; i < numberOfStreams; i++) {
        heap->add(streams[i]);
    }
}

int SortedStream::next() {
    return heap->removeMin();
}

int main(int argc, char const *argv[]) {
    Stream *streams = (Stream *)malloc(NUM_STREAMS*sizeof(streams));
    for (int i = 0; i < NUM_STREAMS; i++) {
        streams[i] = Stream();
    }
    SortedStream sortedStream = SortedStream(streams, NUM_STREAMS);
    int i= 0;
    int last = 0;
    int current;
    //TODO: create better tests
    while(i++ < 10000) {
        current = sortedStream.next();
        assert(current >= last);
        last = current;
    }
    return 0;
}