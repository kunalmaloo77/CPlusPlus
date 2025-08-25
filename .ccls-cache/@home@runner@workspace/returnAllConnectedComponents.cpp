#include <iostream>
#include <vector>
using namespace std;

void dfs(int **edges, int n, int sv, bool *visited, vector<int> &temp) {
  temp.push_back(sv);
  visited[sv] = true;
  for (int i = 0; i < n; ++i) {
    if (!visited[i] && edges[sv][i]) {
      dfs(edges, n, i, visited, temp);
    }
  }
}

vector<vector<int>> connectedComponents(int **edges, int n, bool *visited) {
  vector<vector<int>> ans;
  for (int i = 0; i < n; ++i) {
    if (!visited[i]) {
      vector<int> temp;
      dfs(edges, n, i, visited, temp);
      ans.push_back(temp);
    }
  }
  return ans;
}

int main() {
  int n;
  cout << "Enter number of vertices." << endl;
  cin >> n;
  int **edges = new int *[n];
  for (int i = 0; i < n; ++i) {
    edges[i] = new int[n];
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

  vector<vector<int>> output = connectedComponents(edges, n, visited);
  for (auto component : output) {
    cout << "[";
    for (int i = 0; i < component.size(); i++) {
      cout << component[i];
      if (i < component.size() - 1)
        cout << ",";
    }
    cout << "]" << endl;
  }

  for (int i = 0; i < n; ++i)
    delete[] edges[i];
  delete[] edges;
  delete[] visited;
  return 0;
}