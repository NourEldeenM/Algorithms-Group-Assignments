#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int v, weight;
    Edge(int v, int weight) : v(v), weight(weight) {}
};

void prim(int N, vector<vector<Edge>> &adj, vector<vector<Edge>> &mstGraph)
{
    vector<bool> inMST(N, false);
    vector<int> minEdge(N, INT_MAX);
    vector<int> parent(N, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    minEdge[0] = 0;
    pq.push({0, 0});

    while (!pq.empty())
    {
        int u = pq.top().second; // vertex with min edge weight
        int weight = pq.top().first;
        pq.pop();

        if (inMST[u])
            continue; // skip if already in MST

        inMST[u] = true;

        for (const auto &edge : adj[u])
        {
            int v = edge.v;
            int edgeWeight = edge.weight;

            if (!inMST[v] && edgeWeight < minEdge[v])
            {
                minEdge[v] = edgeWeight;
                parent[v] = u;
                pq.push({edgeWeight, v});
            }
        }
    }

    for (int i = 1; i < N; ++i)
    {
        int u = parent[i];
        int v = i;
        int weight = minEdge[v];
        mstGraph[u].push_back({v, weight});
        mstGraph[v].push_back({u, weight});
    }
}

void bfs(int start, vector<vector<Edge>> &mstGraph, vector<int> &dist)
{
    queue<int> q;
    dist[start] = 0;
    q.push(start);

    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        for (const auto &neighbor : mstGraph[node])
        {
            int nextNode = neighbor.v;
            int weight = neighbor.weight;
            if (dist[nextNode] == -1)
            { // if not visited
                dist[nextNode] = dist[node] + weight;
                q.push(nextNode);
            }
        }
    }
}

int main()
{
    int N, M;
    cin >> N >> M;

    vector<vector<Edge>> adj(N);

    for (int i = 0; i < M; i++)
    {
        int A, B, C;
        cin >> A >> B >> C;
        int weight = (1 << C); // 2^C
        adj[A - 1].push_back(Edge(B - 1, weight));
        adj[B - 1].push_back(Edge(A - 1, weight));
    }

    vector<vector<Edge>> mstGraph(N);

    prim(N, adj, mstGraph);

    long long totalWeight = 0;
    for (int i = 0; i < N; i++)
    {
        vector<int> dist(N, -1); // distances from node i
        bfs(i, mstGraph, dist);

        for (int j = i + 1; j < N; j++)
        {
            totalWeight += dist[j];
        }
    }

    if (totalWeight == 0)
    {
        cout << "0" << endl;
    }
    else
    {
        string binary = "";
        while (totalWeight > 0)
        {
            binary = to_string(totalWeight % 2) + binary;
            totalWeight /= 2;
        }
        cout << binary << endl;
    }

    return 0;
}

// Sample Input
// 5 6
// 1 3 5
// 4 5 0
// 2 1 3
// 3 2 1
// 4 3 4
// 4 2 2
// Sample Output
// 1000100