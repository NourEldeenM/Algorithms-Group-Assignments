#include "bits/stdc++.h"
using namespace std;

int divisionMethod(int key, int n) {
    return key % n;
}

int multiplicationMethod(int key, int n, double A = 0.618033) {
    double fraction = fmod(key * A, 1.0);
    return (int) floor(n * fraction);
}

int midSquareMethod(int key, int n) {
    int r = (int) (log10(n));
    int mid = ((int) (log10(key * key)) - r) / 2;
    return (key * key) / (int) (pow(10, mid)) % (int) (pow(10, r));
}

int foldShiftingMethod(int key, int n) {
    string str = to_string(key);
    int idx = (int) (log10(n)) + 1;
    int sum = 0;
    for (int i = 0; i < str.length(); i += idx) {
        string temp = str.substr(i, idx);
        sum += stoi(temp);
    }
    return sum % n;
}

int foldBoundaryMethod(int key, int n) {
    string str = to_string(key);
    int idx = (int) (log10(n)) + 1;
    int sum = 0;
    for (int i = 0; i < str.length(); i += idx) {
        string temp = str.substr(i, idx);
        if (i == 0 || i >= str.length() - idx) {
            reverse(temp.begin(), temp.end());
        }
        sum += stoi(temp);
    }
    return sum % n;
}
///////////////////////////////////////////////////////////////////////////

struct Node {
    int data;
    Node *next;

    Node(int value) : data(value), next(nullptr) {
    }
};

class LinkedList {
private:
    Node *head;
    Node *tail;

public:
    LinkedList() : head(nullptr), tail(nullptr) {
    }

    void insert(int val) {
        Node *newNode = new Node(val);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    bool search(int value) {
        Node *current = head;
        while (current) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void print() const {
        Node *current = head;
        while (current) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "null" << '\n';
    }

    ~LinkedList() {
        Node *current = head;
        while (current) {
            Node *nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

class HashTable {
private:
    int n; //TableSize
    int greatestPrime; // First prime number smaller than table size
    // Chaining Method
    vector<LinkedList> tableForChaining;
    // Open Addressing and Double Hashing
    vector<int> tableForOpenAddressing;

    bool isPrime(int n) {
        if (n <= 1)
            return false;
        for (int i = 2; i <= sqrt(n); i++) {
            if (n % i == 0)
                return false;
        }
        return true;
    }

    int findLargestPrime(int n) {
        for (int i = n - 1; i > 1; i--) {
            if (isPrime(i)) {
                return i;
            }
        }
        return 2;
    }

    int hash1(int key) {
        return key % n;
    }

    int hash2(int key) {
        return greatestPrime - (key % greatestPrime);
    }

public:
    HashTable(int size) {
        n = size;
        greatestPrime = findLargestPrime(n);
        tableForChaining.resize(n);
        tableForOpenAddressing.resize(n, -1);
        cout << "First prime number smaller than table size (" << n << ") is: "
                << greatestPrime << "\n\n";
    }

    void insertChaining(int key) {
        int index = hash1(key);
        tableForChaining[index].insert(key);
        cout << "Inserted " << key << " into index: " << index << " using Chaining Method." << '\n';
    }

    bool searchChaining(int key) {
        int index = hash1(key);
        return tableForChaining[index].search(key);
    }

    void insertOpenAddressingLinearProbing(int key) {
        int index = hash1(key);
        while (tableForOpenAddressing[index] != -1) {
            index = (index + 1) % n;
        }
        tableForOpenAddressing[index] = key;
        cout << "Inserted " << key << " into index: " << index << " using Open Addressing Linear Probing." << '\n';
    }

    void insertOpenAddressingQuadraticProbing(int key) {
        int index = hash1(key);
        int i = 0;
        while (tableForOpenAddressing[(index + i * i) % n] != -1) {
            i++;
            if (i == n) {
                // Table is full
                cout << "Hash table is full, cannot insert " << key << '\n';
                return;
            }
        }
        tableForOpenAddressing[(index + i * i) % n] = key;
        cout << "Inserted " << key << " into index: " << index << " using Open Addressing Quadratic Probing." << '\n';
    }

    bool searchOpenAddressing(int key) {
        int index = hash1(key);
        while (tableForOpenAddressing[index] != -1) {
            if (tableForOpenAddressing[index] == key) {
                return true;
            }
            index = (index + 1) % n;
        }
        return false;
    }

    bool searchQuadratic(int key) {
        int index = hash1(key);
        int i = 0;
        while (tableForOpenAddressing[(index + i * i) % n] != -1) {
            if (tableForOpenAddressing[(index + i * i) % n] == key) {
                return true;
            }
            i++;
            if (i == n) {
                break;
            }
        }
        return false;
    }

    void insertDoubleHashing(int key) {
        int index1 = hash1(key);
        int index2 = hash2(key);
        int i = 0;
        while (tableForOpenAddressing[(index1 + (i * index2)) % n] != -1) {
            i++;
        }
        tableForOpenAddressing[(index1 + (i * index2)) % n] = key;
        cout << "Inserted " << key << " into index: " << (index1 + i * index2) % n
                << " using Double Hashing Method." << '\n';
    }

    bool searchDoubleHashing(int key) {
        int index1 = hash1(key);
        int index2 = hash2(key);
        int i = 0;
        while (tableForOpenAddressing[(index1 + i * index2) % n] != -1) {
            if (tableForOpenAddressing[(index1 + i * index2) % n] == key) {
                return true;
            }
            i++;
        }
        return false;
    }

    void printChaining() const {
        cout << "Hash Table (Chaining Method):" << '\n';
        for (int i = 0; i < n; ++i) {
            cout << "Index: " << i << ": ";
            tableForChaining[i].print();
        }
    }

    void printOpenAddressing() const {
        for (int i = 0; i < n; ++i) {
            if (tableForOpenAddressing[i] != -1) {
                cout << "Index: " << i << ": " << tableForOpenAddressing[i] << '\n';
            } else {
                cout << "Index: " << i << ": Empty" << '\n';
            }
        }
    }

    void clear() {
        for (auto &linkedList: tableForChaining) {
            linkedList = LinkedList();
        }
        fill(tableForOpenAddressing.begin(), tableForOpenAddressing.end(), -1);
    }
};

int main() {
    int key = 12345678, n = 100;
    cout << "Division Method: " << divisionMethod(key, n) << '\n';
    cout << "Multiplication Method: " << multiplicationMethod(key, n) << '\n';
    cout << "Mid Square Method: " << midSquareMethod(key, n) << '\n';
    cout << "Fold Shifting Method: " << foldShiftingMethod(key, n) << '\n';
    cout << "Fold Boundary Method: " << foldBoundaryMethod(key, n) << '\n';

    cout << "\n Collision Resolution Techinques: \n";
    HashTable hashTable(10);
    hashTable.insertChaining(20);
    hashTable.insertChaining(25);
    hashTable.insertChaining(35);
    hashTable.insertChaining(40);
    cout << '\n';
    hashTable.printChaining();
    cout << "\n***********************************\n";
    if (hashTable.searchChaining(25)) {
        cout << "Key 25 found in Chaining method." << '\n';
    } else {
        cout << "Key 25 not found in Chaining method." << '\n';
    }
    cout << "\n***********************************\n";
    hashTable.clear();
    hashTable.insertOpenAddressingLinearProbing(10);
    hashTable.insertOpenAddressingLinearProbing(20);
    hashTable.insertOpenAddressingLinearProbing(30);
    cout << "\nHash Table (Open Addressing Linear Probing):" << '\n';
    hashTable.printOpenAddressing();
    cout << "\n***********************************\n";
    hashTable.clear();
    hashTable.insertDoubleHashing(15);
    hashTable.insertDoubleHashing(25);
    hashTable.insertDoubleHashing(35);
    cout << "\nHash Table (Open Addressing Double hashing):" << '\n';
    hashTable.printOpenAddressing();
    cout << "\n***********************************\n";
    if (hashTable.searchDoubleHashing(35)) {
        cout << "Key 35 found in Open Addressing Double Hashing." << '\n';
    } else {
        cout << "Key 35 not found in Open Addressing Double Hashing." << '\n';
    }
    cout << "\n***********************************\n";
    hashTable.clear();
    hashTable.insertOpenAddressingQuadraticProbing(10);
    hashTable.insertOpenAddressingQuadraticProbing(20);
    hashTable.insertOpenAddressingQuadraticProbing(15);
    hashTable.insertOpenAddressingQuadraticProbing(7);
    hashTable.insertOpenAddressingQuadraticProbing(30);
    cout << "\nHash Table (Open Addressing Quadratic Probing):" << '\n';
    hashTable.printOpenAddressing();

    cout << "\n***********************************\n";
    if (hashTable.searchQuadratic(15)) {
        cout << "15 found in Open Addressing Quadratic Probing.\n";
    } else {
        cout << "15 not found in Open Addressing Quadratic Probing.\n";
    }
    return 0;
}
