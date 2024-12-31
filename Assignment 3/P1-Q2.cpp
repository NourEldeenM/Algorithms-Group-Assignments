#include <bits/stdc++.h>
using namespace std;

int countOriginalStrings(string s)
{
    int n = s.size();
    vector<long long> dp(n + 1, 0);
    dp[0] = 1; // empty string has one possibility

    for (int i = 1; i <= n; i++)
    {
        // can't be w or m
        if (s[i - 1] == 'm' || s[i - 1] == 'w')
        {
            return 0;
        }

        // current possbility is at least equal to previous one
        dp[i] = dp[i - 1];

        // check for valid pairs "uu" or "nn"
        if (i > 1 && ((s[i - 1] == 'u' && s[i - 2] == 'u') || (s[i - 1] == 'n' && s[i - 2] == 'n')))
        {
            dp[i] = (dp[i] + dp[i - 2]);
        }
    }

    return dp[n];
}

int main()
{
    string s;
    cin >> s;
    cout << countOriginalStrings(s) << endl;
    return 0;
}

// Input    Output
// ouuoharinn  4
// banana      1
// nnn         3
// amanda      0