// Author: sweeliao@163.com.
// Date: 2019/03/18

#ifndef URL_COMPRESS_UTILITY_H
#define URL_COMPRESS_UTILITY_H

#include <string>

namespace url_compression {

// A utility function to get common prefix count of two strings
inline uint8_t common_prefix_count(const char* a, const char* b) {
  uint8_t i = 0;
  size_t len1 = strlen(a);
  size_t len2 = strlen(b);
  while (i < len1 && i < len2 && a[i] == b[i]) {
    ++i;
  }
  return i;
}

}

#endif //URL_COMPRESS_UTILITY_H
