#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// key: index, abs(sum1 - sum2)
// value: minimum difference
// map<pair<int, int>, int> memo;

// int split(vector<int> nums, int index = 0, int sum1 = 0, int sum2 = 0)
// {
//     pair<int, int> combination = make_pair(index, abs(sum1 - sum2));
//     if (memo.find(combination) != memo.end())
//         return memo[combination];

//     if (index == nums.size())
//         return abs(sum1 - sum2);
    

//     memo[combination] = min(split(nums, index + 1, sum1 + nums[index], sum2), split(nums, index + 1, sum1, sum2 + nums[index]));
//     return memo[combination];
// }

int split(vector<int> &nums)
{
    int total_sum = 0;
    for (int num : nums)
        total_sum += num;

    int n = nums.size();
    int offset = total_sum; // handle negative differences
    int max_diff = 2 * total_sum;

    // dP table: dp[i][d] where d ranges from -total_sum to +total_sum
    vector<vector<bool>> dp(n + 1, vector<bool>(max_diff + 1, false));
    dp[0][offset] = true; // base case zero difference at start

    // fill DP table
    for (int i = 1; i <= n; i++)
    {
        for (int d = 0; d <= max_diff; d++)
        {
            if (dp[i - 1][d])
            {
                // include nums[i-1] in the first group
                if (d + nums[i - 1] <= max_diff)
                    dp[i][d + nums[i - 1]] = true;
                // include nums[i-1] in the second group
                if (d - nums[i - 1] >= 0)
                    dp[i][d - nums[i - 1]] = true;
            }
        }
    }

    // find the smallest non-negative difference
    for (int d = 0; d <= total_sum; d++)
        if (dp[n][offset + d])
            return d;

    return -1;
}

int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        // memo.clear();
        int size;
        cin >> size;
        vector<int> nums(size);
        for (int i = 0; i < size; i++)
            cin >> nums[i];

        cout << split(nums) << endl;
    }
}