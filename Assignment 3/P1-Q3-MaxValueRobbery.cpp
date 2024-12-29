// Part 1: Dynamic Programming
// Question: 3
// Knapsack Problem (0/1 Knapsack and Fractional Knapsack)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N;
    cin >> N;
    while (N--) {
        int K, M;
        cin >> K >> M;
//        cin.ignore();
        vector<int> dp(K + 1, 0);

        for (int i = 0; i < M; ++i) {
            int A, B;
            cin >> A >> B;
//            cin.ignore();

            for (int w = K; w >= A; --w) {
                dp[w] = max(dp[w], B + dp[w - A]);
            }
        }

        cout << "Hey stupid robber, you can get " << dp[K] << ".\n";
    }
    return 0;
}
/*
 * Test Case:

Input:
3
34 5
178 12
30 1
13 7
34 8
87 6
900 1
900 25
100 10
27 16
131 9
132 17
6 5
6 23
56 21
100 25
1 25
25 25
100 2

Output:
Hey stupid robber, you can get 8.
Hey stupid robber, you can get 25.
Hey stupid robber, you can get 99.
 */