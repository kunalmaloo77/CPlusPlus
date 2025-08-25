#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

vector<int> getPathBFS(int **edges, int n, int sv, int ev, bool *visited) {
  unordered_map<int, int> parentChild;
  queue<int> bfs;
  bfs.push(sv);
  visited[sv] = true;
  while (!bfs.empty()) {
    int front = bfs.front();
    bfs.pop();
    if (front == ev) {
      vector<int> ans;
      int temp = ev;
      while (temp != sv) {
        if (parentChild.find(temp) == parentChild.end())
          return {};
        ans.push_back(temp);
        temp = parentChild[temp];
      }
      ans.push_back(sv);
      return ans;
    }
    for (int i = 0; i < n; ++i) {
      if (!visited[i] && edges[front][i]) {
        parentChild[i] = front;
        visited[i] = true;
        bfs.push(i);
      }
    }
  }
  return {};
}

vector<int> getPath(int **edges, int n, int sv, int ev, bool *visited) {
  if (sv == ev) {
    return {sv};
  }
  visited[sv] = true;
  for (int i = 0; i < n; ++i) {
    if (!visited[i] && edges[sv][i]) {
      vector<int> path = getPath(edges, n, i, ev, visited);
      if (path.size() != 0) {
        path.push_back(sv);
        return path;
      }
    }
  }
  return {};
}
// 8 10 0 1 0 2 1 6 1 4 2 3 4 5 5 6 4 5 3 7 5 7 0 2
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
  int sv, ev;
  cout << "Enter Starting vertex and ending vertex." << endl;
  cin >> sv >> ev;
  vector<int> output = getPathBFS(edges, n, sv, ev, visited);
  for (int i = 0; i < output.size(); ++i) {
    cout << output.at(i) << " ";
  }

  for (int i = 0; i < n; ++i)
    delete[] edges[i];
  delete[] edges;
  delete[] visited;
  return 0;
}