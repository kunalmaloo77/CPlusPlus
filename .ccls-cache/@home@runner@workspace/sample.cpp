#include <climits>
#include <iostream>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

int maxPathSumData = INT_MIN;

int maxGain(TreeNode *root) {
  if (root == nullptr) {
    return 0;
  }
  int leftSum = max(maxGain(root->left), 0);
  int rightSum = max(maxGain(root->right), 0);
  maxPathSumData = max(maxPathSumData, root->val + leftSum + rightSum);
  return root->val + max(leftSum, rightSum);
}

int maxPathSum(TreeNode *root) {
  maxGain(root);
  return maxPathSumData;
}

int main() {
  TreeNode *root = new TreeNode(-10);
  root->left = new TreeNode(9);
  root->right = new TreeNode(20);

  root->right->left = new TreeNode(15);
  root->right->right = new TreeNode(-25);

  root->right->right->left = new TreeNode(3);
  root->right->right->right = new TreeNode(4);

  cout << maxPathSum(root) << endl; // Expected output: 39

  // cleanup (not fully deleting all nodes here for brevity)
  delete root;
  return 0;
}