// Author: sweeliao@163.com.
// Date: 2019/03/20

#include "gtest/gtest.h"
#include "avl_tree_compression.h"
#include "url_retrieve.h"

namespace url_compression {

class UrlRetrieveTest : public ::testing::Test {
 public:
  TreeCompression compressor;
  std::unique_ptr<UrlRetrieve> retrieve;
  std::shared_ptr<NodeArray> nodes;

  std::vector<std::string> urls = {
      "http://www.baidu.com",
      "http://www.qq.com",
      "http://www.qq.com/hubei",
      "http://www.hao123.com",
      "http://www.alibaba.com",
      "http://www.google.com",
      "http://www.facebook.com"};

 protected:
  void SetUp() override {
    for (auto& url: urls) {
      compressor.add(url);
    }
    nodes = compressor.dump_tree();
    retrieve = std::make_unique<UrlRetrieve>(nodes.get(),
                                             &compressor.ptr_vec_,
                                             compressor.block_.get());
  }
};

TEST_F(UrlRetrieveTest, Exists) {
  EXPECT_TRUE(retrieve->exists("http://www.hao123.com"));
}

TEST_F(UrlRetrieveTest, Get) {
  for (auto i = 0; i < urls.size(); ++i) {
    EXPECT_EQ(urls[i], retrieve->get(i + 1));
  }
}

}
