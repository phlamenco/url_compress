// Author: sweeliao@163.com.
// Date: 2019/03/18

#include "url_block.h"

namespace url_compression {

UrlBlock::UrlBlock() {
  head_ = (char*)calloc(1, BLOCK_SIZE);
  cap_ = BLOCK_SIZE;
  len_ = 0;
}

UrlBlock::~UrlBlock() {
  free(head_);
}

char* UrlBlock::add_url(size_t ref_id, uint8_t common_prefix, const char* url) {
  size_t url_len = strlen(url) + 1;
  size_t need_size = sizeof(ref_id) + sizeof(common_prefix) + url_len;
  uint64_t new_len = len_ + need_size;
  if (new_len > cap_) {
    if (!enlarge()) {
      return nullptr;
    }
  }
  char* current_ptr = head_ + len_;
  url_t* url_elem = reinterpret_cast<url_t*>(current_ptr);
  url_elem->ref_id = ref_id;
  url_elem->common_prefix = common_prefix;
  memcpy(&(url_elem->diff_url), url, url_len);
  len_ = new_len;
  return current_ptr;
}

const url_t UrlBlock::get_url(char* ptr) {
  url_t new_url;
  url_t* url = reinterpret_cast<url_t*>(ptr);
  new_url.ref_id = url->ref_id;
  new_url.common_prefix = url->common_prefix;
  new_url.diff_url = ptr + sizeof(url->ref_id) + sizeof(url->common_prefix);
  return new_url;
}

bool UrlBlock::enlarge() {
  uint64_t new_cap = FACTOR * cap_;
  char* tmp_buf = (char*)calloc(1, new_cap);
  if (tmp_buf == nullptr) {
    return false;
  }
  memcpy(tmp_buf, head_, len_);
  free(head_);
  head_ = tmp_buf;
  cap_ = new_cap;
  return true;
}

}
