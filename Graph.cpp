#include <iostream>
#include <queue>
#include <vector>
using namespace std;

vector<int> BFS(vector<vector<int>> &graph, vector<bool> &visited) {
  if (graph.size() == 0)
    return {};
  queue<int> que;
  vector<int> ans;
  visited[0] = true;
  que.push(0);
  ans.push_back(0);
  while (que.size() != 0) {
    int front = que.front();
    que.pop();
    for (auto ele : graph[front]) {
      if (!visited[ele]) {
        ans.push_back(ele);
        que.push(ele);
        visited[ele] = true;
      }
    }
  }
  return ans;
}

void DFS(vector<vector<int>> &graph, vector<bool> &visited, int sv,
         vector<int> &ans) {
  visited[sv] = true;
  for (auto ele : graph[sv]) {
    if (!visited[ele]) {
      ans.push_back(ele);
      DFS(graph, visited, ele, ans);
    }
  }
}

int main() {
  int n;
  cout << "Enter Number of vertices" << endl;
  cin >> n;
  int e;
  cout << "Enter Number of edges" << endl;
  cin >> e;

  vector<vector<int>> graph(n);
  for (int i = 0; i < e; ++i) {
    int sv, ev;
    cin >> sv >> ev;
    if (sv >= n || ev >= n || sv < 0 || ev < 0) {
      cout << "Note: Enter valid sv or ev" << endl;
      --i;
      continue;
    }
    graph[sv].push_back(ev);
    graph[ev].push_back(sv);
  }

  vector<bool> visited(n, false);
  vector<int> ans = BFS(graph, visited);
  vector<int> ans2;
  fill(visited.begin(), visited.end(), false);
  ans2.push_back(0);
  cout << "BFS:" << endl;
  DFS(graph, visited, 0, ans2);
  for (int i = 0; i < ans.size(); ++i) {
    cout << ans[i] << ",";
  }
  cout << endl;
  cout << "DFS:" << endl;
  for (int i = 0; i < ans2.size(); ++i) {
    cout << ans2[i] << ",";
  }
  return 0;
}