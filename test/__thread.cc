#include <iostream>
#include <pthread.h>
#include <list>
using namespace std;
__thread list<int> *tls = NULL;

void print_t(list<int> *t)
{
  list<int>::const_iterator iter = t->begin();
  while (iter != t->end())
  {
    cout << t << " " << *iter << endl;
    iter++;
  }
}
int main()
{
  tls = new list<int>();
  list<int> *t1 = tls;
  t1->push_back(1);
  print_t(t1);
  tls = new list<int>();
  list<int> *t2 = tls;
  t2->push_back(2);
  print_t(t2);
  return 0;
}
