#ifndef _MY_TEST_
#define _MY_TEST_
#include <gtest/gtest.h>



inline int MyTest(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#endif // _MY_TEST_
