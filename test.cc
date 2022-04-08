#include <iostream>
#include <stack>
#include <string>
#include <stdlib.h>

using namespace std;

int check(string &s, int start)
{
  stack<char> tmp;
  int i = start;
  for (; i < s.size(); i++)
  {
    if (s[i] == '[')
    {
      tmp.push(s[i]);
    }
    else if (s[i] == ']')
    {
      tmp.pop();
      if (tmp.empty())
      {
        return i;
      }
    }
  }
  return -1;
}

string test(string &s)
{
  string result;
  int count = 0;
  for (int i = 0; i < s.size(); i++)
  {
    if (s[i] == '[')
    {
      // []
      int end = check(s, i);
      int start = i + 1;
      string tmp;
      while (count--)
      {
       tmp += s.substr(start, end - start);
      }
      if (end + 1 < s.size())
      {
        tmp += s.substr(end + 1, s.size() - end);
      }
      result += test(tmp);
    }
    else if ('a' <= s[i] && s[i] <= 'z')
    {
      // 字符
      result += s[i];
    }
    else
    {
      // 数字
      count = atoi(s.c_str());
    }
  }
  return result;
}



int main()
{
  string s1 = "3[a]2[bc]";
  cout << test(s1) << endl;
  return 0;
}
