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

        vector<int> dp(K + 1, 0);

        for (int i = 0; i < M; ++i) {
            int A, B;
            cin >> A >> B;

            for (int w = K; w >= A; --w) {
                dp[w] = max(dp[w], dp[w - A] + B);
            }
        }

        cout << "Hey stupid robber, you can get " << dp[K] << "." << endl;
    }
    return 0;
}
