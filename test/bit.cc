#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <bitset>
using namespace std;
#define bit_1_mask (0xffffffffffffffff)
#define bit_2_mask (bit_1_mask << 64)
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
  printf("%x\n====\n", block);
  bitset<65> bitco1;
  bitset<8 * 4> bitco2;
  bitset<8 * 1024> bitco3;
  cout << sizeof(bitco1) << endl;
  cout << sizeof(bitco2) << endl;
  cout << sizeof(bitco3) << endl;
  bitset<512> bitco4;
  unsigned long bit_long = bitco4.to_ulong();
  cout << sizeof(bit_long) << " " << sizeof(bitco4) << endl;
  // cout << bitco4.to_string() << endl;
  bitset<1024> bit5(bit_1_mask);
  cout << bit5.to_string() << endl;
  bit5 <<= 64;
  cout << bit5.to_string() << endl;
  cout << sizeof(unsigned long) << endl;
  bit5 = 0xff;
  cout << bit5.to_string() << endl;
  return 0;
}
