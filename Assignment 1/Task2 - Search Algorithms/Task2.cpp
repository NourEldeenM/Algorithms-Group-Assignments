#include <bits/stdc++.h>

using namespace std;

// O(n) time, O(1) space
int sequentialSearchIterative(const vector<int> &arr, int target) {
    for (int i = 0; i < (int) arr.size(); i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

// O(n) time, O(n) space (for recursion calls in stack)
int sequentialSearchRecursive(const vector<int> &arr, int target, int i = 0) {
    if (i >= (int) arr.size()) {
        return -1;
    }
    if (arr[i] == target) {
        return i;
    }
    return sequentialSearchRecursive(arr, target, i + 1);
}

// O(Log n) time, O(1) space
int binarySearchIterative(const vector<int> &arr, int target) {
    int low = 0;
    int high = (int) arr.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

// O(Log n) time, O(Log n) space (for recursion calls in stack)
int binarySearchRecursive(const vector<int> &arr, int target, int low, int high) {
    if (low > high) {
        return -1;
    }
    int mid = low + (high - low) / 2;
    if (arr[mid] == target) {
        return mid;
    } else if (arr[mid] < target) {
        return binarySearchRecursive(arr, target, mid + 1, high);
    } else {
        return binarySearchRecursive(arr, target, low, mid - 1);
    }
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 7, 9};
    int target = 7;
    int result = sequentialSearchIterative(arr, target);
    if (result != -1) {
        cout << "Sequential Search (Iterative): Element found at index " << result << '\n';
    } else {
        cout << "Sequential Search (Iterative): Element not found" << '\n';
    }
    ///////////////////////////////////////////
    result = sequentialSearchRecursive(arr, target);
    if (result != -1) {
        cout << "Sequential Search (Recursive): Element found at index " << result << '\n';
    } else {
        cout << "Sequential Search (Recursive): Element not found" << '\n';
    }
    ///////////////////////////////////////////
    //Binary Search only works on sorted arrays, O(n) to check if array is sorted and O(n Log n) to sort
    if (!is_sorted(arr.begin(), arr.end())) {
        sort(arr.begin(), arr.end());
    }
    result = binarySearchIterative(arr, target);
    if (result != -1) {
        cout << "Binary Search (Iterative): Element found at index " << result << '\n';
    } else {
        cout << "Binary Search (Iterative): Element not found" << '\n';
    }
    ///////////////////////////////////////////
    result = binarySearchRecursive(arr, target, 0, (int) arr.size() - 1);
    if (result != -1) {
        cout << "Binary Search (Recursive): Element found at index " << result << '\n';
    } else {
        cout << "Binary Search (Recursive): Element not found" << '\n';
    }
    return 0;
}