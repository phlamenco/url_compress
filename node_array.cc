// Author: sweeliao@163.com.
// Date: 2019/03/20

#include "node_array.h"

namespace url_compression {

void NodeArray::alloc(size_t size) {
  nodes_.reserve(size + 1);
  for (auto i = 0; i < size; ++i) {
    Node n;
    memset(&n, 0, sizeof(Node));
    nodes_.push_back(n);
  }
}

void NodeArray::insert(uint32_t id, uint32_t left_id, uint32_t right_id, uint8_t height) {
  Node& n = nodes_[id];
  n.left = 0x0fffffff & left_id;
  n.right = 0x0fffffff & right_id;
  n.hh = height >> 4;
  n.hl = 0x0f & height;
}

uint32_t NodeArray::get_root_index() const {
  return nodes_[0].left;
}

void NodeArray::set_root_index(uint32_t idx) {
  nodes_[0].left = idx;
}

const Node& NodeArray::get_node(uint32_t id) const {
  return nodes_[id];
}

uint8_t Node::height() const {
  return uint8_t(hl | (hh << 4));
}

}
