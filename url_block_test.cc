// Author: sweeliao@163.com.
// Date: 2019/03/19

#include "gtest/gtest.h"
#include "url_block.h"

namespace url_compression {

class UrlBlockTest : public ::testing::Test {
 public:
  UrlBlockTest() {
    block = std::make_unique<UrlBlock>();
  }

  std::unique_ptr<UrlBlock> block;
};

TEST_F(UrlBlockTest, AddAndGetUrl) {
  auto ptr = block->add_url(0, 19, "qq.com");
  EXPECT_TRUE(ptr != nullptr);
  auto url = block->get_url(ptr);
  EXPECT_EQ(0, url.ref_id);
  EXPECT_EQ(19, url.common_prefix);
  EXPECT_EQ(std::string("qq.com"), std::string(url.diff_url));
}

TEST_F(UrlBlockTest, AutoEnlarge) {
  char* bigStr = (char*)malloc(10241);
  memset(bigStr, 'q', 10241);
  auto ptr = block->add_url(0, 19, bigStr);
  EXPECT_TRUE(ptr != nullptr);
  EXPECT_EQ(20480, block->capacity());
  auto url = block->get_url(ptr);
  EXPECT_EQ(0, url.ref_id);
  EXPECT_EQ(19, url.common_prefix);
  EXPECT_EQ(std::string(bigStr), std::string(url.diff_url));
  free(bigStr);
}

}
