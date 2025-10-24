#include <bits/stdc++.h>
using namespace std;


//Time Complexity of adjacency matrix is O(V^2 logV)
vector<int> dijkstra(vector<vector<int>> &graph, int vertices) {
  vector<bool> visited(vertices, false);
  vector<int> dist(vertices, INT_MAX);
  dist[0] = 0;
  // stores min distances so min pq
  priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
  pq.push({0,0}); // dist, neighbour
  // O(V)
  while (!pq.empty()) {
    pair<int,int> dist_neigh = pq.top();
    pq.pop();
    visited[dist_neigh.second] = true; 
    // O(v)
    for (int i = 0; i < vertices; ++i) {
      if (graph[dist_neigh.second][i] != 0 && !visited[i]) {
        dist[i] = min(dist[i], graph[dist_neigh.second][i] + dist_neigh.first);
        pq.push({dist[i],i}); // O(logV)
      }
    }
  }
  return dist;
}

//5 6 0 1 4 0 2 8 1 2 2 1 3 5 3 4 4 2 4 9

int main() {
  int vertices;
  cin >> vertices;
  int edges;
  cin >> edges;
  vector<vector<int>> graph(vertices, vector<int>(vertices, 0));
  for (int i = 0; i < edges; ++i) {
    int sv, ev, w;
    cin >> sv >> ev >> w;
    graph[sv][ev] = w;
    graph[ev][sv] = w;
  }
  vector<int> dist = dijkstra(graph, vertices);
  for (int i = 0; i < dist.size(); ++i) {
    cout << dist[i] << ",";
  }
  return 0;
}

