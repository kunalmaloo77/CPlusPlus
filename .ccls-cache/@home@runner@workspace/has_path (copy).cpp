#include <iostream>
using namespace std;

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
  if (hasPath(edges, n, sv, ev, visited)) {
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