#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

bool validPath(int n, vector<vector<int>>& edges, int src, int dest) {
    // Special case: if source and destination are the same
    if(src == dest) return true;

    unordered_map<int, vector<int>> graph;
    for(const auto &edge : edges){
        int u = edge[0]; int v = edge[1];
        graph[u].push_back(v); graph[v].push_back(u);
    }

    // BFS
    queue<int> q; unordered_set<int> visited;
    q.push(src); visited.insert(src);
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        for(int adjacent : graph[cur]){
            if(adjacent == dest) return true;
            if(visited.find(adjacent) == visited.end()){
                q.push(adjacent); visited.insert(adjacent);
            }
        }
    }
    return false;
}

int main() {
    // Example 1
    int n1 = 3;
    vector<vector<int>> edges1 = {{0, 1}, {1, 2}, {2, 0}};
    int source1 = 0, destination1 = 2;

    if (validPath(n1, edges1, source1, destination1)) {
        cout << "Output: true" << endl; // Expected: true
    } else {
        cout << "Output: false" << endl;
    }

    // Example 2
    int n2 = 6;
    vector<vector<int>> edges2 = {{0, 1}, {0, 2}, {3, 5}, {5, 4}, {4, 3}};
    int source2 = 0, destination2 = 5;

    if (validPath(n2, edges2, source2, destination2)) {
        cout << "Output: true" << endl; // Expected: false
    } else {
        cout << "Output: false" << endl;
    }

    return 0;
}
/*
Complexity:
Time: 𝑂(𝑛 + 𝑒), where 𝑛 is the number of vertices and 𝑒 is the number of edges.
Space: 𝑂(𝑛 + 𝑒), for the adjacency list and visited set.
 */