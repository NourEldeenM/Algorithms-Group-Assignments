#include <iostream>
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

vector<int> heapsortDesc(vector<int> arr)
{
    maxHeap heap;
    for (int i = 0; i < arr.size(); i++)
    {
        heap.insertElement(arr[i]);
    }

    vector<int> output;
    while (heap.size() != 0)
    {
        output.push_back(heap.peek());
        heap.pop_max();
    }

    return output;
}

vector<int> heapsortAsc(vector<int> arr)
{
    vector<int> output, desc = heapsortDesc(arr);

    while (desc.size() != 0)
    {
        output.push_back(desc.back());
        desc.pop_back();
    }

    return output;
}

int main()
{
    cout << "\n################Heap Testing####################\n";

    maxHeap heap;
    // Test insertElement and peek
    heap.insertElement(10);
    cout << "Peek after inserting 10: " << heap.peek() << endl; // Should print 10
    heap.insertElement(20);
    cout << "Peek after inserting 20: " << heap.peek() << endl; // Should print 20
    heap.insertElement(5);
    cout << "Peek after inserting 5: " << heap.peek() << endl; // Should still print 20
    // Test pop
    cout << "Pop: " << heap.pop_max() << endl;         // Should print 20
    cout << "Peek after pop: " << heap.peek() << endl; // Should print 10
    cout << "Smallest: " << heap.get_min() << endl;
    cout << "Pop: " << heap.pop_max() << endl;         // Should print 10
    cout << "Peek after pop: " << heap.peek() << endl; // Should print 5
    cout << "Pop: " << heap.pop_max() << endl;         // Should print 5
    cout << "Smallest: " << heap.get_min() << endl;
    cout << "Peek after pop: " << heap.peek() << endl; // Should print -1 (empty heap)

    cout << "\n###############Priority Queue##################\n";
    priorityQueue pq;
    // Insert elements into the priority queue
    pq.push(20);
    pq.push(15);
    pq.push(30);
    pq.push(10);
    // Print the size of the priority queue
    cout << "Priority queue size: " << pq.size() << endl;
    // Remove and print elements in priority order
    cout << "Elements in priority order (max-heap): ";
    while (pq.size() > 0)
    {
        cout << pq.pop() << " ";
    }
    cout << endl;

    cout << "\n################Heap Sort####################\n";

    vector<int> v = {5, 2, 4, 1, 77, 8, 2};
    v = heapsortDesc(v);
    cout << "Sorted Descending: ";
    for (const int i : v)
    {
        cout << i << ' ';
    }
    cout << endl;

    v = heapsortAsc(v);
    cout << "Sorted Ascending: ";
    for (const int i : v)
    {
        cout << i << ' ';
    }
    cout << endl;

    return 0;
}
