#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

map<int, long int> memo = {};

long solve(int n, vector<long> c, int startIndex = 0) {
    if (memo.find(n) != memo.end())
        return memo[n];
    if (n == 0)
        return 1;
    if (n < 0)
        return 0;

    long sum = 0;
    for (int i = startIndex; i < c.size(); i++)
    {
        long remainder = n - c[i];
        memo[remainder] = solve(remainder, c, i);
        sum += memo[remainder];
    }
    
    return sum;
}


long getWays(int n, vector<long> c) {
    return solve(n, c);
}

int main()
{
    vector<long> c = {2, 5, 3, 6};
    long n = 10;
    cout << getWays(n, c) << endl;
}