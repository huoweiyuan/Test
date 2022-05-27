#include "gtest/gtest.h"
#include <vector>


using namespace std;
bool canJump(vector<int>& nums) {
  vector<int> _result(nums.size());
  _result[0] = nums[0];
  for (int i = 1; i < nums.size(); i++) {
    if (_result[i - 1] == 0) {
      return false;
    }
    if (nums[i] > _result[i - 1] - 1) {
      _result[i] = nums[i];
    } else if (nums[i] <= _result[i - 1] - 1) {
      _result[i] = _result[i - 1] - 1;
    }
  }
  return true;
}


TEST(LEETCODE, 55) {
  vector<int> test1 = {2,3,1,1,4};
  EXPECT_EQ(true, canJump(test1));

  vector<int> test2 = {3,2,1,0,4};
  EXPECT_EQ(false, canJump(test2));

  vector<int> test3 = {0,1};
  EXPECT_EQ(false, canJump(test3));

}
