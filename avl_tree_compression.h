// Author: sweeliao@163.com.
// Date: 2019/03/18

#ifndef URL_COMPRESS_AVL_TREE_H
#define URL_COMPRESS_AVL_TREE_H

#include <cstdint>
#include <vector>
#include <memory>
#include "url_block.h"

namespace url_compression {

struct TreeNode {
  size_t index;
  int height;
  TreeNode* left;
  TreeNode* right;
};

class TreeCompression {
 public:
  TreeCompression();

  ~TreeCompression();

  bool add(const std::string& url);

  bool exists(const std::string& url);

  void print_tree();

 private:

  TreeNode* insert(TreeNode* node,
                   size_t ref_id,
                   uint8_t common_prefix,
                   const char* url);

  TreeNode* find(TreeNode* node, const char* url);

  void _print_tree(TreeNode* node);

  std::string get_complete_url(size_t idx);

  // A utility function to get the height of the tree
  int height(TreeNode* n) {
    if (n == nullptr)
      return 0;
    return n->height;
  }

  /**
   * T1, T2 and T3 are subtrees of the tree
   * rooted with y (on the left side) or x (on
   * the right side)
        y                               x
       / \     Right Rotation          /  \
      x   T3   - - - - - - - >        T1   y
     / \       < - - - - - - -            / \
    T1  T2     Left Rotation            T2  T3
   * Keys in both of the above trees follow the
   * following order
   * keys(T1) < key(x) < keys(T2) < key(y) < keys(T3)
   * So BST property is not violated anywhere.
   */

  // A utility function to right rotate subtree rooted with y
  TreeNode* right_rotate(TreeNode* y);

  // A utility function to left rotate subtree rooted with x
  TreeNode* left_rotate(TreeNode* x);

  // Get Balance factor of node N
  int get_balance(TreeNode* N);

  size_t get_next_idx() const {
    return ptr_vec_.size();
  }

  void free_tree(TreeNode* node);

  TreeNode* root_ = nullptr;
  std::unique_ptr<UrlBlock> block_;
  std::vector<char*> ptr_vec_;
};

}

#endif //URL_COMPRESS_AVL_TREE_H
