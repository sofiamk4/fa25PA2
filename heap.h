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

        // Check if heap is full
        if (size >= 64) {
            cout<<"Heap is full."<<endl;
            return;
        }

        // Insert index at end of heap
        data[size] = idx;

        // Increment size of heap
        size++;

        // Restore order of heap calling upheap()
        upheap(size - 1, weightArr);
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()

        // Check if heap is empty
        if (size == 0) {
            cout<<"Heap is empty."<<endl;
            return -1;
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
        downheap(0, weightArr);
        return min;
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        // Check if position is valid
        if (pos < 0 || pos > size) {
            cout<<"Invalid index."<<endl;
             return;
        }

        // Declare the child node as the current position
        int child = pos;

        // Loop while position is not 0, not at root
        while (child > 0) {
            // Calculate parent position
            int parent = (child - 1) / 2;

            // Compare child and parent positions
            if (weightArr[data[child]] < weightArr[data[parent]]) {
                // Swap positions if child is less than parent
                int temp = data[child];
                data[child] = data[parent];
                data[parent] = temp;
                child = parent;
            }
            else {
                // Return once child is no longer less than parent
                return;
            }
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        // Declare parent as current position
        int parent = pos;
        // Declare left child
        int leftChild = 2 * parent + 1;

        // Loop while the left child is less than the size of heap
        while (leftChild < size) {
            // Start by declaring smallest position as the left child
            int smallest = leftChild;
            // Declare right child
            int rightChild = 2 * parent + 2;
            // Compare right and left child if the right child is less than the size of the heap
            if (rightChild < size) {
                if (weightArr[data[rightChild]] < weightArr[data[leftChild]]) {
                    // Set smallest position as the right child if the left child is greater
                    smallest = rightChild;
                }
            }
            // Now compare parent with the actual smallest child
            if (weightArr[data[parent]] > weightArr[data[smallest]]) {
                // Swap parent and smallest child if parent is greater
                int temp = data[smallest];
                data[smallest] = data[parent];
                data[parent] = temp;
                parent = smallest;
                // Update left child to reflect new parent position and loop again
                leftChild = 2 * parent + 1;
            }
            else {
                // Return once the parent is no longer greater than the smallest child
                return;
            }
        }
    }
};

#endif