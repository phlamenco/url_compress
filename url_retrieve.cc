// Author: sweeliao@163.com.
// Date: 2019/03/20

#include "url_retrieve.h"

namespace url_compression {

UrlRetrieve::UrlRetrieve(NodeArray* nodes,
                         std::vector<char*>* ptr_vec,
                         UrlBlock* block)
    : nodes_(nodes), ptr_vec_(ptr_vec), block_(block) {
  root_idx_ = nodes_->get_root_index();
}

bool UrlRetrieve::exists(const std::string& url) const {
  return exists_impl(root_idx_, url);
}

std::string UrlRetrieve::get(uint32_t id) const {
  auto ptr = (*ptr_vec_)[id];
  url_t url = block_->get_url(ptr);
  auto ref_id = url.ref_id;
  if (ref_id == 0)
    return url.diff_url;
  return get(ref_id).substr(0, url.common_prefix) + url.diff_url;
}

bool UrlRetrieve::exists_impl(uint32_t index, const std::string& url) const {
  if (index == 0)
    return false;
  auto current_url = get(index);
  auto cmp = current_url.compare(url);
  if (cmp == 0) {
    return true;
  } else if (cmp > 0){
    return exists_impl(nodes_->get_node(index).left, url);
  } else {
    return exists_impl(nodes_->get_node(index).right, url);
  }
}

}
