#include <bits/stdc++.h>

using namespace std;

int main() {
    int t, w, n;
    int totalTime[40], quantityOfGold[40], depth[40];
    int dp[40][1010]; //Maximum gold possible using first i treasures with j time remaining
    bool flag = false;
    while (cin >> t >> w) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> depth[i] >> quantityOfGold[i];
            totalTime[i] = 3 * depth[i] * w;
        }
        for (int j = 0; j <= t; j++) {
            dp[0][j] = 0; // 0 treasures => 0 gold
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= t; j++) {
                if (totalTime[i] <= j)
                    dp[i][j] = max(dp[i - 1][j], quantityOfGold[i] + dp[i - 1][j - totalTime[i]]);
                else
                    dp[i][j] = dp[i - 1][j];
            }
        }
        if (flag) {
            cout << '\n';
        }
        flag = true;
        int ans[40], recovered = 0, sum = 0;
        while (n) {
            if (dp[n][t] != dp[n - 1][t]) {
                ans[recovered++] = n;
                t -= totalTime[n];
                sum += quantityOfGold[n];
            }
            n--;
        }
        cout << sum << '\n' << recovered << '\n';
        for (int i = recovered - 1; i >= 0; i--) {
            cout << depth[ans[i]] << ' ' << quantityOfGold[ans[i]] << '\n';
        }
    }
}

/*
Example Input (^D (Ctrl + D) to stop taking input)
210 4
3
10 5
10 1
7 2
Example Output
7
2
10 5
7 2
 */
