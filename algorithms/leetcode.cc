#include "leetcode.h"
#include <gtest/gtest.h>

TEST(LEETCODE, maxSubArray0)
{
  Leetcode leetcode;
  vector<int> input = {-2,1,-3,4,-1,2,1,-5,4};
  int result = 6;
  EXPECT_EQ(result, leetcode.maxSubArray(input));
}


int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

}
