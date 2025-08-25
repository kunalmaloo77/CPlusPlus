#include <iostream>
#include <queue>
using namespace std;

bool hasPathBFS(int **edges, int n, int sv, int ev, bool *visited) {
  queue<int> graphQueue;
  graphQueue.push(sv);
  visited[sv] = true;
  while (!graphQueue.empty()) {
    int front = graphQueue.front();
    graphQueue.pop();
    if (front == ev) {
      return true;
    }
    for (int i = 0; i < n; ++i) {
      if (!visited[i] && edges[front][i]) {
        graphQueue.push(i);
        visited[i] = true;
      }
    }
  }
  return false;
}
// 5 5 0 1 1 2 2 0 2 3 3 4 0 4

bool hasPath(int **edges, int n, int sv, int ev, bool *visited) {
  if (sv == ev) {
    return true;
  }
  visited[sv] = true;
  for (int i = 0; i < n; ++i) {
    if (!visited[i] && edges[sv][i]) {
      return hasPath(edges, n, i, ev, visited);
    }
  }
  return false;
}

int main() {
  int n;
  cout << "Enter number of vertices." << endl;
  cin >> n;
  int **edges = new int *[n];
  for (int i = 0; i < n; ++i) {
    edges[i] = new int[n]; // allocate row
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      edges[i][j] = 0;
    }
  }
  int edgesCount;
  cout << "Enter number of edges." << endl;
  cin >> edgesCount;
  for (int i = 0; i < edgesCount; ++i) {
    int sv;
    int ev;
    cin >> sv >> ev;
    edges[sv][ev] = 1;
    edges[ev][sv] = 1;
  }
  bool *visited = new bool[n];
  for (int i = 0; i < n; ++i) {
    visited[i] = false;
  }
  int sv;
  int ev;
  cout << "Enter Starting vertex and ending vertex." << endl;
  cin >> sv >> ev;
  if (hasPathBFS(edges, n, sv, ev, visited)) {
    cout << "Has Path" << endl;
  } else {
    cout << "Does not have path." << endl;
  }
  for (int i = 0; i < n; ++i)
    delete[] edges[i];
  delete[] edges;
  delete[] visited;
  return 0;
}