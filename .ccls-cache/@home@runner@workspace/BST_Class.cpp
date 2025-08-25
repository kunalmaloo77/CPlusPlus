#include <climits>
#include <iostream>
#include <queue>
using namespace std;

template <typename T> class BinaryTreeNode {
  T data;
  BinaryTreeNode<T> *left;
  BinaryTreeNode<T> *right;

public:
  BinaryTreeNode(T data) {
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
  }
  ~BinaryTreeNode() {
    delete left;
    delete right;
  }
  T getData() { return data; }
  BinaryTreeNode<T> *getLeft() { return left; }
  BinaryTreeNode<T> *getRight() { return right; }
  void setData(T data) { this->data = data; }
  void setLeft(BinaryTreeNode<T> *node) { this->left = node; }
  void setRight(BinaryTreeNode<T> *node) { this->right = node; }
};

class BST {
  BinaryTreeNode<int> *root;

public:
  BST() { this->root = nullptr; }
  ~BST() { delete root; }

private:
  bool hasDataHelper(int data, BinaryTreeNode<int> *root) {
    if (root == nullptr) {
      return false;
    }
    if (root->getData() == data) {
      return true;
    }
    if (data > root->getData()) {
      return hasDataHelper(data, root->getRight());
    }
    return hasDataHelper(data, root->getLeft());
  }

public:
  bool hasData(int data) { return hasDataHelper(data, this->root); }

private:
  BinaryTreeNode<int> *insertDataHelper(int data, BinaryTreeNode<int> *root) {
    if (root == nullptr) {
      BinaryTreeNode<int> *node = new BinaryTreeNode<int>(data);
      return node;
    }

    if (data > root->getData()) {
      root->setRight(insertDataHelper(data, root->getRight()));
    }
    if (data <= root->getData()) {
      root->setLeft(insertDataHelper(data, root->getLeft()));
    }
    return root;
  }

public:
  void insertData(int data) { this->root = insertDataHelper(data, this->root); }

private:
  BinaryTreeNode<int> *deleteDataHelper(int data, BinaryTreeNode<int> *root) {
    // base case
    if (root == nullptr) {
      return nullptr;
    }
    int rootData = root->getData();
    // go right
    if (rootData < data) {
      root->setRight(deleteDataHelper(data, root->getRight()));
      return root;
    }
    // go left
    else if (rootData > data) {
      root->setLeft(deleteDataHelper(data, root->getLeft()));
      return root;
    }
    // root's data and given data are equal
    else {
      // if both child are null
      if (root->getLeft() == nullptr && root->getRight() == nullptr) {
        delete root;
        return nullptr;
      }
      // if left child is null
      else if (root->getLeft() == nullptr) {
        BinaryTreeNode<int> *node = root->getRight();
        root->setRight(nullptr);
        delete root;
        return node;
      }
      // if right child is null
      else if (root->getRight() == nullptr) {
        BinaryTreeNode<int> *node = root->getLeft();
        root->setLeft(nullptr);
        delete root;
        return node;
      }
      // both not null
      else {
        BinaryTreeNode<int> *maxNode = root->getLeft();
        while (maxNode->getRight() != nullptr) {
          maxNode = maxNode->getRight();
        }
        root->setData(maxNode->getData());
        root->setLeft(deleteDataHelper(maxNode->getData(), root->getLeft()));
        return root;
      }
    }
    return nullptr;
  }

public:
  void deleteData(int data) { this->root = deleteDataHelper(data, this->root); }

public:
  void printBST() {
    if (root == nullptr) {
      return;
    }
    queue<BinaryTreeNode<int> *> pendingNodes;
    pendingNodes.push(root);
    while (pendingNodes.size() != 0) {
      BinaryTreeNode<int> *front = pendingNodes.front();
      pendingNodes.pop();
      cout << front->getData() << ":";
      if (front->getLeft() != nullptr) {
        cout << "L" << front->getLeft()->getData() << ",";
        pendingNodes.push(front->getLeft());
      }
      if (front->getRight() != nullptr) {
        cout << "R" << front->getRight()->getData();
        pendingNodes.push(front->getRight());
      }
      cout << endl;
    }
  }
};

int main() {
  BST b;
  b.insertData(1);
  b.insertData(2);
  b.insertData(3);
  b.insertData(4);
  // b.deleteData(3);
  if (b.hasData(2)) {
    cout << "Yes your node is present." << endl;
  } else {
    cout << "Sorry node not found." << endl;
  }
  b.printBST();
  return 0;
}