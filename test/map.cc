#include <iostream>
#include <map>
#include <string>
#include <string.h>
using namespace std;

// typedef map<int, string> sub_map;
// typedef map<int, sub_map> main_map;
// int main(int argc, char const *argv[])
// {
//   main_map m;
//   m[1][1] = "a";
//   m[1][2] = "b";
//   cout << m[1][1] << " " << m[1][2] << endl;
//   return 0;
// }




struct test_struct
{
  int a;
  char b[11];
  test_struct()
  {
    
  }
  test_struct(const test_struct &_b)
  {
    a = _b.a;
    strcpy(b, _b.b);
  }
};

class test_class
{
 private:
  map<int, test_struct> test;
 public:
  void add_data()
  {
    test_struct t;
    t.a = 1;
    strcpy(t.b, "asd");
    for (int i= 0; i < 10; i++)
    {
      test[i] = t;
    }
  }
  test_class() {}
  virtual ~test_class() {}
};

class testb : public test_class
{
  
};

int main()
{
  testb *a = new testb();
  a->add_data();
  testb *b = new testb();
  *b = *a;
  delete a;
  delete b;
  return 0;
}
