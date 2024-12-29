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

/*
 * Constraints:
     ● 1<=g.length <= 3 * 104
     ● 0<=s.length <= 3 * 104
     ● 1<=g[i], s[j] <= 231- 1


 * Test Cases:

 Example 1:
 Input: g = [1,2,3], s = [1,1]
 Output: 1
 Explanation: You have 3 children and 2 cookies. The greed factors of 3 children are 1, 2, 3.
 And even though you have 2 cookies, since their size is both 1, you could only make the
 child whose greed factor is 1 content.
 You need to output 1.


 Example 2:
 Input: g = [1,2], s = [1,2,3]
 Output: 2
 Explanation: You have 2 children and 3 cookies. The greed factors of 2 children are 1, 2.
 You have 3 cookies and their sizes are big enough to gratify all of the children,
 You need to output 2.

 */