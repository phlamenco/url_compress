// Author: sweeliao@163.com.
// Date: 2019/03/18

#include <cstdlib>
#include "avl_tree.h"

namespace UrlCompression {

Node::Node(char* p) : ptr(p) {
  left = nullptr;
  right = nullptr;
  height = 1; // new node is initially added at leaf
}

}