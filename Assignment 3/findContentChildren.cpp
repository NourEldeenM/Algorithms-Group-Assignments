// Part 2: Greedy algorithms and MST
// Question: 1
// Approach: Sort children and cookies by size and greedily assign cookies to children with the smallest possible greed factor.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int findContentChildren(vector<int>& g, vector<int>& s) {
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());

    int i = 0, j = 0;
    int contentChildren = 0;

    while (i < g.size() && j < s.size()) {
        if (s[j] >= g[i]) {
            contentChildren++;
            i++;
        }
        j++;
    }

    return contentChildren;
}

int main() {
    // Example 1
    vector<int> g1 = {1, 2, 3};
    vector<int> s1 = {1, 1};
    cout << "Example 1 Output: " << findContentChildren(g1, s1) << endl;
    // Output should be like the following: Example 1 Output: 1

    // Example 2
    vector<int> g2 = {1, 2};
    vector<int> s2 = {1, 2, 3};
    cout << "Example 2 Output: " << findContentChildren(g2, s2) << endl;
    // Output should be like the following: Example 2 Output: 2

    return 0;
}
