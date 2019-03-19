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

 private:

  TreeNode* insert(TreeNode* node,
                   size_t ref_id,
                   uint8_t common_prefix,
                   const char* url);

  TreeNode* find(TreeNode* node, const char* url);

  std::string get_complete_url(size_t idx);

  // A utility function to get the height of the tree
  int height(TreeNode* n) {
    if (n == nullptr)
      return 0;
    return n->height;
  }

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
