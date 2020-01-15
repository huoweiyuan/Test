#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <bitset>
int main()
{
  // 位域
  struct mbit
  {
    int i:4;
  };
	
  uint8_t block = 0xFF;
  block = block | (~0x1);
  std::cout << std::bitset<16>(~0x1) << " " << std::bitset<8>(block) << std::endl;
  block = block & (~0x8);
  std::cout << std::bitset<8>(block) << std::endl;
  block = block | 0x8;
  std::cout << std::bitset<8>(block) << std::endl;
  printf("%x\n", block);
  return 0;
}
