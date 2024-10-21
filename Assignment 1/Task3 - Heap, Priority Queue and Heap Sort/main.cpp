#include <iostream>
#include "implementation.cpp"
// #include "headers.h"

using namespace std;

int main()
{
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

    cout << "Pop: " << heap.pop_max() << endl; // Should print 5
    cout << "Smallest: " << heap.get_min() << endl;
    cout << "Peek after pop: " << heap.peek() << endl; // Should print -1 (empty heap)

    return 0;
}
