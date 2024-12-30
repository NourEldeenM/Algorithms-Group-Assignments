#include "bits/stdc++.h"
using namespace std;

int N, M, G, S, numberOfCurrentEdges;
long long ans = 1e18;

struct edge {
    int from, to;
    long long gi, si;
};

edge e[50010], mstEdges[50010];
int parent[50010];

// Union-Find find function to get the representative of a set
int find(const int x) {
    if (x == parent[x])
        return x;
    return parent[x] = find(parent[x]);
}

bool cmp(const edge &edge1, const edge &edge2) {
    if (edge1.gi != edge2.gi)
        return edge1.gi < edge2.gi;
    return edge1.si < edge2.si;
}

long long multiply(const long long a, const long long b) {
    if (!a || !b)
        return 0;
    // Check for overflow
    if (a > LLONG_MAX / b) {
        return LLONG_MAX;
    }
    return a * b;
}

void Kruskal() {
    numberOfCurrentEdges = 0;
    ans = LLONG_MAX;
    for (int i = 0; i < M; i++) {
        for (int j = 1; j <= N; j++) {
            parent[j] = j;
        }
        mstEdges[numberOfCurrentEdges++] = e[i];
        long long maxSilver = 0; // maximum silver
        // Sort current edges by silver
        for (int j = numberOfCurrentEdges - 1; j >= 1; j--) {
            if (mstEdges[j].si < mstEdges[j - 1].si)
                swap(mstEdges[j], mstEdges[j - 1]);
        }
        int numberOfMstEdges = 0;
        // build MST with current edges
        for (int j = 0; j < numberOfCurrentEdges; ++j) {
            int u = find(mstEdges[j].from);
            int v = find(mstEdges[j].to);
            if (u != v) {
                // if u and v are not in the same set => no cycle
                maxSilver = max(maxSilver, mstEdges[j].si);
                mstEdges[numberOfMstEdges++] = mstEdges[j];
                parent[u] = v; // Union
            }
            if (numberOfMstEdges == N - 1)
                break;
        }
        if (numberOfMstEdges == N - 1) {
            // Update minimum cost if current solution is better
            long long goldCost = multiply(e[i].gi, G);
            long long silverCost = multiply(maxSilver, S);
            if (goldCost != LLONG_MAX and silverCost != LLONG_MAX) {
                if (LLONG_MAX - goldCost >= silverCost) {
                    ans = min(ans, goldCost + silverCost);
                }
            }
        }
        numberOfCurrentEdges = numberOfMstEdges;
    }
}

int main() {
    cin >> N >> M >> G >> S;
    for (int i = 0; i < M; i++) {
        cin >> e[i].from >> e[i].to >> e[i].gi >> e[i].si;
    }
    // Sort all edges by gold requirement
    sort(e, e + M, cmp);
    Kruskal();
    if (ans == LLONG_MAX)
        cout << "-1\n";
    else
        cout << ans << '\n';
    return 0;
}

/*
Example Input
3 3
2 1
1 2 10 15
1 2 4 20
1 3 5 1
Example Output
30
 */
