#include <iostream>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

uint64_t get_trx_no_from_str(const char *trx_no_str)
{
  const char *start = trx_no_str;
  const char *end = start + strlen(trx_no_str);
  const char *buf = end - 1;
  uint64_t trx_no = 0;
  while (buf > start)
  {
    if (*buf == ':')
    {
      end = buf;
      break;
    }
    buf--;
  }

  buf = end - 1;
  char tmp_trx_no[64] = {0};
  while (buf > start)
  {
    if (*buf == '-'|| *buf == ':')
    {
      break;
    }
    buf--;
  }
  if (buf == start)
  {
    strcpy(tmp_trx_no, start);
    trx_no = atoi(tmp_trx_no);
  }
  else
  {
    int length = end - buf - 1;
    strncpy(tmp_trx_no, buf + 1, length);
    tmp_trx_no[length] = '\0';
    trx_no = atoi(tmp_trx_no);
  }
  return trx_no;
}

using namespace std;

int main()
{
  cout << get_trx_no_from_str("1-971") << endl;
  return 0;
}
