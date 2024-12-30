#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n), lis(n, 1);

    for (int i = 0; i < n; i++)
        cin >> arr[i];

    // initialize lis array with 1 to set base case & loop from 1 to n
    for (int i = 1; i < n; i++)
    {
        // loop through all elements to the left of current element (i)
        for (int j = 0; j < i; j++)
        {
            // if current element (i) greater than the element to his left (j)
            if (arr[j] < arr[i])
                lis[i] = max(lis[i], lis[j] + 1);
        }
    }
    cout << *max_element(lis.begin(), lis.end()) << endl;
}