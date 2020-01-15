#include <iostream>

#define BT_SHUFFLE(x,y,z,w) ((w)<<6 | (z)<<4 | (y)<<2 | (x))
#define bt_splat_ps( _i ) BT_SHUFFLE(_i,_i,_i,_i)
int main()
{
  std::cout << bt_splat_ps( 0x80) << std::endl;
  return 0;
}
