#include <bits/stdc++.h>
using namespace std;

int leastInterval(vector<char> &tasks, int n)
{
    // frequency array for tasks (26 chars)
    vector<int> freq(26, 0);
    for (char task : tasks)
    {
        freq[task - 'A']++;
    }

    int maxFreq = *max_element(freq.begin(), freq.end());
    int maxCount = count(freq.begin(), freq.end(), maxFreq);
    int minLength = (maxFreq - 1) * (n + 1) + maxCount;

    return max(minLength, (int)tasks.size());
}

int main()
{
    int x, n;
    cout << "Enter Number of Tasks: ";
    cin >> x;
    cout << "Enter the gap (n): ";
    cin >> n;
    vector<char> tasks(x);
    for (int i = 0; i < x; i++)
    {
        cout << "Enter task " << i + 1 << ":";
        cin >> tasks[i];
    }
    cout << leastInterval(tasks, n);

    // vector<char> tasks1 = {'A', 'A', 'A', 'B', 'B', 'B'};
    // int n1 = 2;
    // cout << leastInterval(tasks1, n1) << endl; // Output: 8

    // vector<char> tasks2 = {'A', 'C', 'A', 'B', 'D', 'B'};
    // int n2 = 1;
    // cout << leastInterval(tasks2, n2) << endl; // Output: 6

    // vector<char> tasks3 = {'A', 'A', 'A', 'B', 'B', 'B'};
    // int n3 = 3;
    // cout << leastInterval(tasks3, n3) << endl; // Output: 10

    return 0;
}