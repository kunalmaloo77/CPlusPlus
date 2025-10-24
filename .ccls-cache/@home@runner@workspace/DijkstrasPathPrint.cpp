#include "limits.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

vector<int> getPathDijkstras(vector<vector<pair<int, int>>> graph, int sv,
                             int ev, int vertices) {
  vector<bool> visited(vertices, false);
  vector<int> distances(vertices, INT_MAX);
  // to store child <-> parent
  unordered_map<int, int> map;

  distances[sv] = 0;
  // dist, node
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      smallestPathQueue;
  smallestPathQueue.push({0, sv});
  while (!smallestPathQueue.empty()) {
    pair<int, int> top = smallestPathQueue.top();
    int minDist = top.first;
    int minNode = top.second;
    smallestPathQueue.pop();

    if (visited[minNode])
      continue;
    visited[minNode] = true;

    for (auto neigh : graph[minNode]) {
      int weightOfNeigh = neigh.first;
      int neighNode = neigh.second;
      if (!visited[neighNode] &&
          distances[neighNode] > distances[minNode] + weightOfNeigh) {
        distances[neighNode] = distances[minNode] + weightOfNeigh;
        map[neighNode] = minNode;
        smallestPathQueue.push({distances[neighNode], neighNode});
      }
    }
  }

  vector<int> path;
  if (distances[ev] == INT_MAX)
    return path;
  for (int at = ev; at != sv; at = map[at]) {
    path.push_back(at);
  }
  path.push_back(sv);
  reverse(path.begin(), path.end());
  return path;
}

int main() {
  int vertices;
  cout << "Enter Number of vertices" << endl;
  cin >> vertices;
  int edges;
  cout << "Enter number of edges" << endl;
  cin >> edges;
  
  // pair -> weight, node
  vector<vector<pair<int, int>>> graph(vertices);
  for (int i = 0; i < edges; ++i) {
    int sv, ev, w;
    // dist , node
    cin >> sv >> ev >> w;
    graph[sv].push_back({w, ev});
    graph[ev].push_back({w, sv});
  }

  int sv, ev;
  cout << "Enter Starting and ending vertex" << endl;
  cin >> sv >> ev;

  vector<int> path = getPathDijkstras(graph, sv, ev, vertices);
  for (int i = 0; i < path.size(); ++i) {
    cout << path[i] << "->";
  }
  return 0;
}
