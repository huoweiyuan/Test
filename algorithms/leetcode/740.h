#ifndef _GTEST_
#define _GTEST_
#include <gtest/gtest.h>
#endif

#include <vector>
#include <algorithm>

using namespace std;
int rob(vector<int> &nums);
int deleteAndEarn1(vector<int> &nums) {
  int _max = 0;
  for_each(nums.begin(), nums.end(), [&_max](int &num) {
    if (num > _max)
      _max = num;
  });
  vector<int> _earns(_max + 1);
  for_each(nums.begin(), nums.end(), [&_earns](int &num) {
    _earns[num] += num;
  });
  return rob(_earns);
}

int deleteAndEarn2(vector<int> &nums) {
  sort(nums.begin(), nums.end());
  vector<int> _sum = {nums[0]};
  int _count = 0;
  for (int i = 1; i < nums.size(); i++) {
    if (nums[i] - nums[i - 1] == 1) {
      _sum.push_back(nums[i]);
    } else if (nums[i] == nums[i - 1]) {
      _sum.back() += nums[i];
    } else {
      _count += rob(_sum);
      _sum = {nums[i]};
    }
  }
  _count += rob(_sum);
  return _count;
}

int rob(vector<int> &nums) {
  if (nums.size() == 1) {
    return nums.front();
  } else if (nums.size() == 2) {
    return max(nums.front(), nums.back());
  }

  vector<int> result(3);
  result[0] = nums.front();
  result[1] = max(nums[0], nums[1]);
  for (int i = 2; i < nums.size(); i++) {
    result[2] = max(result[0] + nums[i], result[1]);
    result[0] = result[1];
    result[1] = result[2];
  }
  return result[2];
}

TEST(LEETCODE, 740_deleteAndEarn1) {
  vector<int> nums = {3,4,2};
  EXPECT_EQ(6, deleteAndEarn1(nums));
  vector<int> nums1 = {2,2,3,3,3,4};
  EXPECT_EQ(9, deleteAndEarn1(nums1));
}

TEST(LEETCODE, 740_deleteAndEarn2) {
  vector<int> nums = {3,4,2};
  EXPECT_EQ(6, deleteAndEarn1(nums));
  vector<int> nums1 = {2,2,3,3,3,4};
  EXPECT_EQ(9, deleteAndEarn1(nums1));
}
