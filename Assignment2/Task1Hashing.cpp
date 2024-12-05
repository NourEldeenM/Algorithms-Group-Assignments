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

class HashTable {
private:
    int n; //TableSize
    int greatestPrime; // First prime number smaller than table size

    // Chaining Method
    vector<vector<int> > tableForChaining;
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
                << greatestPrime << '\n';
    }


    void insertChaining(int key) {
        int index = hash1(key);
        tableForChaining[index].push_back(key);
        cout << "Inserted " << key << " into index: " << index << " using Chaining Method." << '\n';
    }


    bool searchChaining(int key) {
        int index = hash1(key);
        for (int k: tableForChaining[index]) {
            if (k == key) {
                return true;
            }
        }
        return false;
    }

    // Open Addressing: Linear Probing
    void insertOpenAddressingLinearProbing(int key) {
        int index = hash1(key);
        while (tableForOpenAddressing[index] != -1) {
            index = (index + 1) % n;
        }
        tableForOpenAddressing[index] = key;
        cout << "Inserted " << key << " into index: " << index << " using Open Addressing Method." << '\n';
    }

    // Open Addressing: Quadratic Probing
    void insertOpenAddressingQuadraticProbing(int key) {
        int index = hash1(key);
        int i = 0;
        while (tableForOpenAddressing[(index + i * i) % n] != -1) {
            i++;
            if (i == n) {
                // Table is full
                cout << "Hash table is full! Cannot insert " << key << '\n';
                return;
            }
        }
        tableForOpenAddressing[(index + i * i) % n] = key;
    }

    // Search using linear probing
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

    // Search using quadratic probing
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
        return false; // Key not found
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

    void printChaining() {
        cout << "Hash Table (Chaining Method):" << '\n';
        for (int i = 0; i < n; ++i) {
            cout << "Index: " << i << ": ";
            for (int key: tableForChaining[i]) {
                cout << key << " -> ";
            }
            cout << "null" << '\n';
        }
    }

    void printOpenAddressing() {
        cout << "Hash Table (Double Hashing Method):" << '\n';
        for (int i = 0; i < n; ++i) {
            if (tableForOpenAddressing[i] != -1) {
                cout << "Index: " << i << ": " << tableForOpenAddressing[i] << '\n';
            } else {
                cout << "Index: " << i << ": Empty" << '\n';
            }
        }
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
    cout << "\n***********************************\n";
    hashTable.insertOpenAddressingLinearProbing(10);
    hashTable.insertOpenAddressingLinearProbing(20);
    hashTable.insertOpenAddressingLinearProbing(30);

    hashTable.insertDoubleHashing(15);
    hashTable.insertDoubleHashing(25);
    hashTable.insertDoubleHashing(35);
    cout << "\n***********************************\n";

    hashTable.printChaining();
    cout << "\n***********************************\n";

    hashTable.printOpenAddressing();
    cout << "\n***********************************\n";

    if (hashTable.searchChaining(25)) {
        cout << "Key 25 found in Chaining method." << '\n';
    } else {
        cout << "Key 25 not found in Chaining method." << '\n';
    }

    cout << "\n***********************************\n";
    if (hashTable.searchOpenAddressing(30)) {
        cout << "Key 30 found in Open Addressing." << '\n';
    } else {
        cout << "Key 30 not found in Open Addressing." << '\n';
    }

    hashTable.insertOpenAddressingQuadraticProbing(10);
    hashTable.insertOpenAddressingQuadraticProbing(20);
    hashTable.insertOpenAddressingQuadraticProbing(15);
    hashTable.insertOpenAddressingQuadraticProbing(7);
    hashTable.insertOpenAddressingQuadraticProbing(30);

    cout << "\n***********************************\n";
    hashTable.printOpenAddressing();

    cout << "\n***********************************\n";
    cout << "Search for 15: " << (hashTable.searchQuadratic(15) ? "Found" : "Not Found") << '\n';
    cout << "Search for 25: " << (hashTable.searchQuadratic(25) ? "Found" : "Not Found") << '\n';
    return 0;
}