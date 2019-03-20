// Author: sweeliao@163.com.
// Date: 2019/03/20

#ifndef URL_COMPRESS_NODE_ARRAY_H
#define URL_COMPRESS_NODE_ARRAY_H

#include <cstdint>
#include <vector>

namespace url_compression {

struct Node {
  uint32_t left:28;
  uint32_t hh:4;
  uint32_t right:28;
  uint32_t hl:4;

  uint8_t height() const;
};

class NodeArray {
 public:
  void alloc(size_t size);

  // id starts from 1
  void insert(uint32_t id, uint32_t left_id, uint32_t right_id, uint8_t height);

  // id starts from 1
  const Node& get_node(uint32_t id) const;

  uint32_t get_root_index() const;

  void set_root_index(uint32_t idx);

 private:
  std::vector<Node> nodes_;
};

}

#endif //URL_COMPRESS_NODE_ARRAY_H
