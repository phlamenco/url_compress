// Author: sweeliao@163.com.
// Date: 2019/03/20

#ifndef URL_COMPRESS_URL_RETRIEVE_H
#define URL_COMPRESS_URL_RETRIEVE_H

#include "node_array.h"
#include "url_block.h"
#include <memory>

namespace url_compression {

class UrlRetrieve {
 public:
  UrlRetrieve(NodeArray* nodes,
              std::vector<char*>* ptr_vec,
              UrlBlock* block);

  bool exists(const std::string& url) const;

  std::string get(uint32_t id) const;

 private:
  bool exists_impl(uint32_t index, const std::string& url) const;

  NodeArray* nodes_;
  std::vector<char*>* ptr_vec_;
  UrlBlock* block_;
  uint32_t root_idx_;
};

}

#endif //URL_COMPRESS_URL_RETRIEVE_H
