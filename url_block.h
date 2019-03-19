// Author: sweeliao@163.com.
// Date: 2019/03/18

#ifndef URL_COMPRESS_COMPRESSEDURLARRAY_H
#define URL_COMPRESS_COMPRESSEDURLARRAY_H

#include <cstdint>
#include <string>

namespace url_compression {

#pragma pack(push, 1)

struct url_t {
  size_t ref_id;
  uint8_t common_prefix;
  char* diff_url;
};

class UrlBlock {
 public:
  UrlBlock();

  ~UrlBlock();

  char* add_url(size_t ref_id, uint8_t common_prefix, const char* url);

  const url_t get_url(char* ptr);

  uint64_t capacity() const {
    return cap_;
  }

  uint64_t len() const {
    return len_;
  }

  const char* get_buf() const {
    return head_;
  }

 private:
  bool enlarge();

  static const int FACTOR = 2;
  static const int BLOCK_SIZE = 10240;

  char* head_ = nullptr;
  uint64_t cap_;
  uint64_t len_;
};

#pragma pack(pop)

}

#endif //URL_COMPRESS_COMPRESSEDURLARRAY_H
