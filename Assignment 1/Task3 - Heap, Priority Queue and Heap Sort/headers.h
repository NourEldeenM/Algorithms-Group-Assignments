#ifndef HEADERS_H
#define HEADERS_H

#include <vector>
using namespace std;

class maxHeap
{
    vector<int> array = {0}; // Start with a dummy 0 element for 1-based index heap

    int getLeftChildIndex(int parentIndex);
    int getRightChildIndex(int parentIndex);
    int getParentIndex(int childIndex);

    bool hasLeftChild(int index);
    bool hasRightChild(int index);
    bool hasParent(int index);

    int getLeftChild(int index);
    int getRightChild(int index);
    int getParent(int index);

    void swap(int index1, int index2);

    void heapifyDown();

    void heapifyUp();

public:
    void insertElement(int data);
    int peek();
    int pop_max();
    int get_min();
    int size();
};

class priorityQueue
{
private:
    maxHeap heap;
public:
    void push(int element);
    int pop();
    int size();
};

#endif