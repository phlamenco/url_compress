// Author: sweeliao@163.com.
// Date: 2019/03/18

#include <cstdlib>
#include <iostream>
#include "avl_tree_compression.h"
#include "utility.h"

namespace url_compression {

TreeCompression::TreeCompression() {
  // push head node
  ptr_vec_.push_back(nullptr);
  block_ = std::make_unique<UrlBlock>();
}

TreeCompression::~TreeCompression() {
  free_tree(root_);
}

bool TreeCompression::add(const std::string& url) {
  auto new_root = insert(root_, 0, 0, url.c_str());
  if (new_root != nullptr) {
    root_ = new_root;
    return true;
  } else {
    return false;
  }
}

bool TreeCompression::exists(const std::string& url) {
  return find(root_, url.c_str()) != nullptr;
}

uint32_t TreeCompression::count() const {
  return node_count(root_);
}

std::shared_ptr<NodeArray> TreeCompression::dump_tree() {
  auto node_array = std::make_shared<NodeArray>();
  node_array->alloc(node_count(root_));
  dump_tree_impl(root_, node_array.get());
  node_array->set_root_index(root_->index);
  return node_array;
}

void TreeCompression::dump_tree_impl(TreeNode* node, NodeArray* nodes) {
  if (node == nullptr)
    return;
  uint32_t left_id = 0;
  uint32_t right_id = 0;
  uint8_t height = 0;
  if (node->left != nullptr) {
    left_id = node->left->index;
  }
  if (node->right != nullptr) {
    right_id = node->right->index;
  }
  height = node->height;
  nodes->insert(node->index, left_id, right_id, height);
  dump_tree_impl(node->left, nodes);
  dump_tree_impl(node->right, nodes);
}

uint32_t TreeCompression::node_count(TreeNode* node) const {
  if (node == nullptr)
    return 0;
  return node_count(node->left) + node_count(node->right) + 1;
}

TreeNode* TreeCompression::find(TreeNode* node, const char* url) {
  if (node == nullptr)
    return nullptr;
  auto node_url = get_complete_url(node->index);
  int cmp = std::strcmp(node_url.c_str(), url);
  if (cmp == 0) {
    return node;
  } else if (cmp < 0) {
    return find(node->right, url);
  } else {
    return find(node->left, url);
  }
}

TreeNode* TreeCompression::insert(TreeNode* node,
                                  size_t ref_id,
                                  uint8_t common_prefix,
                                  const char* url) {
  if (node == nullptr) {
    node = new TreeNode;
    node->index = get_next_idx();
    node->height = 1;
    node->left = nullptr;
    node->right = nullptr;
    auto ptr = block_->add_url(ref_id, common_prefix, url + common_prefix);
    if (ptr == nullptr) {
      delete node;
      return nullptr;
    }
    ptr_vec_.push_back(ptr);
    return node;
  } else {
    std::string node_complete_url = get_complete_url(node->index);
    uint8_t common_count = common_prefix_count(node_complete_url.c_str(), url);
    if (common_count > common_prefix) {
      ref_id = node->index;
      common_prefix = common_count;
    }
    int cmp = std::strcmp(node_complete_url.c_str(), url);
    if (cmp == 0) {
      return node;
    } else if (cmp < 0) {
      node->right = insert(node->right, ref_id, common_prefix, url);
    } else {
      node->left = insert(node->left, ref_id, common_prefix, url);
    }
    node->height = 1 + std::max(height(node->left), height(node->right));
    int balance = get_balance(node);
    // If this node becomes unbalanced, then
    // there are 4 cases
    if (balance > 1) {
      std::string left_complete_url = get_complete_url(node->left->index);
      int cmp = std::strcmp(url, left_complete_url.c_str());
      if (cmp < 0) {
        return right_rotate(node);
      } else if (cmp > 0) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
      }
    } else if (balance < -1) {
      std::string right_complete_url = get_complete_url(node->right->index);
      int cmp = std::strcmp(right_complete_url.c_str(), url);
      if (cmp < 0) {
        return left_rotate(node);
      } else if (cmp > 0) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
      }
    }
    return node;
  }
}

std::string TreeCompression::get_complete_url(size_t idx) {
  url_t url_elem = block_->get_url(ptr_vec_[idx]);
  if (url_elem.ref_id == 0) {
    return url_elem.diff_url;
  } else {
    return get_complete_url(url_elem.ref_id).substr(0, url_elem.common_prefix) + url_elem.diff_url;
  }
}

TreeNode* TreeCompression::right_rotate(TreeNode* y) {
  TreeNode *x = y->left;
  TreeNode *T2 = x->right;

  // Perform rotation
  x->right = y;
  y->left = T2;

  // Update heights
  y->height = std::max(height(y->left), height(y->right))+1;
  x->height = std::max(height(x->left), height(x->right))+1;

  // Return new root
  return x;
}

TreeNode* TreeCompression::left_rotate(TreeNode* x) {
  TreeNode *y = x->right;
  TreeNode *T2 = y->left;

  // Perform rotation
  y->left = x;
  x->right = T2;

  // Update heights
  x->height = std::max(height(x->left), height(x->right))+1;
  y->height = std::max(height(y->left), height(y->right))+1;

  // Return new root
  return y;
}

int TreeCompression::get_balance(TreeNode* node) {
  if (node == nullptr)
    return 0;
  return height(node->left) - height(node->right);
}

void TreeCompression::free_tree(TreeNode* node) {
  if (node->left != nullptr)
    free_tree(node->left);
  if (node->right != nullptr)
    free_tree(node->right);
  delete node;
}

}