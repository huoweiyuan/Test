#include <iostream>
char _dig_vec_upper[] =
  "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char _dig_vec_lower[] =
  "0123456789abcdefghijklmnopqrstuvwxyz";

void mysql_hex_string(char *to, const char *from, unsigned int length)
{
  char *to0= to;
  const char *end;
            
  for (end= from + length; from < end; from++)
  {
    *to++= _dig_vec_upper[((unsigned char) *from) >> 4];
    *to++= _dig_vec_upper[((unsigned char) *from) & 0x0F];
  }
  *to= '\0';
}

void array_to_hex(char *to, const unsigned char *str, unsigned int len)
{
  const unsigned char *str_end= str + len;
  for (; str != str_end; ++str)
  {
    *to++= _dig_vec_lower[((unsigned char) *str) >> 4];
    *to++= _dig_vec_lower[((unsigned char) *str) & 0x0F];
  }
}

int main()
{
  unsigned char test[] = "6E6968616F";
  char re[36];
  // mysql_hex_string(re, test, strlen(test));
  array_to_hex(re, test, 10);
  std::cout << re << std::endl;
  return 0;
}
