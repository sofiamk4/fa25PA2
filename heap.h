//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        // Check if index is a valid integer
        if (size <= idx || idx < 0) {
            cout<<"Invalid index."<<endl;
            return;
        }

        // Check if heap is full
        if (size >= 64) {
            cout<<"Heap is full."<<endl;
            return;
        }

        // Insert index at end of heap
        data[size] = weightArr[idx];

        // Increment size of heap
        size++;

        // Restore order of heap calling upheap()
        upheap(data[size - 1], weightArr);
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()

        // Check if heap is empty
        if (size == 0) {
            cout<<"Heap is empty."<<endl;
            return 0;
        }

        // Assign root to temp variable
        int min = data[0];

        // Replace root with last element
        data[0] = data[size - 1];

        // Decrement size of heap
        size--;

        // Check if heap is now empty and return smallest index
        if (size == 0) {
            return min;
        }

        // Restore order of heap calling downheap() and return smallest index
        downheap(data[size], weightArr);
        return min;
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
    }
};

#endif