#include "headers.h"
#include <iostream>
#include <vector>

using namespace std;

int maxHeap::getLeftChildIndex(int parentIndex)
{
    return 2 * parentIndex;
}
int maxHeap::getRightChildIndex(int parentIndex)
{
    return 2 * parentIndex + 1;
}
int maxHeap::getParentIndex(int childIndex)
{
    return childIndex / 2;
}

bool maxHeap::hasLeftChild(int index)
{
    return getLeftChildIndex(index) < array.size();
}
bool maxHeap::hasRightChild(int index)
{
    return getRightChildIndex(index) < array.size();
}
bool maxHeap::hasParent(int index)
{
    return index > 1; // Parent exists for index > 1
}

int maxHeap::getLeftChild(int index)
{
    return array[getLeftChildIndex(index)];
}
int maxHeap::getRightChild(int index)
{
    return array[getRightChildIndex(index)];
}
int maxHeap::getParent(int index)
{
    return array[getParentIndex(index)];
}

void maxHeap::swap(int index1, int index2)
{
    int temp = array[index1];
    array[index1] = array[index2];
    array[index2] = temp;
}

void maxHeap::heapifyDown()
{
    int index = 1;
    while (hasLeftChild(index))
    {
        int largerChildIndex = getLeftChildIndex(index);
        if (hasRightChild(index) && getRightChild(index) > getLeftChild(index))
            largerChildIndex = getRightChildIndex(index);

        if (array[index] > array[largerChildIndex])
            return;
        else
        {
            swap(index, largerChildIndex);
            index = largerChildIndex;
        }
    }
}

void maxHeap::heapifyUp()
{
    int index = array.size() - 1;
    while (hasParent(index) && getParent(index) < array[index])
    {
        swap(index, getParentIndex(index));
        index = getParentIndex(index);
    }
}

void maxHeap::insertElement(int data)
{
    array.push_back(data);
    heapifyUp();
}

int maxHeap::peek()
{
    if (array.size() > 1)
        return array[1];
    return -1; // In case of empty heap
}

int maxHeap::pop_max()
{ // extract largest element (root since it is max heap)
    if (array.size() <= 1)
        return -1;
    int item = peek();
    array[1] = array.back(); // Replace root with last element
    array.pop_back();        // Remove the last element
    heapifyDown();
    return item;
}

int maxHeap::get_min()
{
    if (array.size() == 1)
        return -1;
    int start = array.size() / 2, smallest = INT_MAX;
    for (int i = start; i < array.size(); i++)
        smallest = array[i] < smallest ? array[i] : smallest;
    return smallest;
}

int maxHeap::size()
{
    return array.size() - 1;
}

int priorityQueue::size()
{
    return heap.size();
}
int priorityQueue::pop()
{
    return heap.pop_max();
}
void priorityQueue::push(int element)
{
    return heap.insertElement(element);
}