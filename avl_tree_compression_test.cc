// Author: sweeliao@163.com.
// Date: 2019/03/19

#include "avl_tree_compression.h"
#include "gtest/gtest.h"

namespace url_compression {

class TreeCompressionTest : public ::testing::Test {
 public:
  TreeCompression compressor;

 protected:
  void SetUp() override {
    compressor.add("http://www.baidu.com");
    compressor.add("http://www.qq.com");
    compressor.add("http://www.qq.com/hubei");
    compressor.add("http://www.hao123.com");
    compressor.add("http://www.alibaba.com");
    compressor.add("http://www.google.com");
    compressor.add("http://www.facebook.com");
  }
};

TEST_F(TreeCompressionTest, Exist) {
  EXPECT_TRUE(compressor.exists("http://www.qq.com"));
}

}
