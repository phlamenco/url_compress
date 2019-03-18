// Author: sweeliao@163.com.
// Date: 2019/03/18

#ifndef URL_COMPRESS_AVL_TREE_H
#define URL_COMPRESS_AVL_TREE_H

#include <cstdint>

namespace UrlCompression {

struct Node {
  char* ptr;
  int height;
  Node* left;
  Node* right;

  explicit Node(char* p);

  Node* insert(char* p);

 private:
  // A utility function to right rotate subtree rooted with y
  Node* rightRotate(Node* y);

  // A utility function to left rotate subtree rooted with x
  Node* leftRotate(Node* x);

  // Get Balance factor of node N
  int getBalance(Node* N);
};

}

#endif //URL_COMPRESS_AVL_TREE_H
