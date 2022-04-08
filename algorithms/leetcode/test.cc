// g++ -std=c++11 test.cc -lgtest -lpthread
#include "global_header.h"
int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
