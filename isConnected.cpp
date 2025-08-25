#include <iostream>
using namespace std;

void helper(int **edges, int n, int sv, bool *visited) {
  visited[sv] = true;
  for (int i = 0; i < n; ++i) {
    if (!visited[i] && edges[sv][i] == 1) {
      helper(edges, n, i, visited);
    }
  }
}

bool isConnected(int **edges, int n, int sv, bool *visited) {
  helper(edges, n, sv, visited);
  for (int i = 0; i < n; ++i) {
    if (!visited[i])
      return false;
  }
  return true;
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

  if (isConnected(edges, n, 0, visited)) {
    cout << "Connected";
  } else {
    cout << "Disconnected";
  }

  for (int i = 0; i < n; ++i)
    delete[] edges[i];
  delete[] edges;
  delete[] visited;
  return 0;
}