#include <iostream>

// link: https://stackoverflow.com/questions/4986673/c11-rvalues-and-move-semantics-confusion-return-statement

using namespace std;

class Test
{
 public:
  bool m_copy;
  int m_i;
 public:
  Test() = delete;

 public:
  Test(int i)
    :m_i(i),
     m_copy(false)
  {
    cout << "Test::Test ";
    cout << "m_i = " << m_i << endl;
  }

  Test(const Test &t)
  {
    m_i = t.m_i;
    m_copy = true;
    cout << "Test::Test(const Test&) ";
    cout << "m_i = " << m_i << endl;
  }

  ~Test()
  {
    cout << "Test::~Test ";
    cout << "m_i = " << m_i << " copy = " << m_copy << endl;
  }
};

Test return_test1(void)
{
  Test t(1);
  return t;
}

Test&& return_test2(void)
{
  Test t(2);
  return move(t);
}

Test return_test3(void)
{
  Test t(3);
  cout << "return_test3 1" << endl;
  Test &&t3 = move(t);
  cout << "return_test3 2 " << "m_i = " << t3.m_i << " copy = " << t3.m_copy
       << endl;

  return t3;
}

int main()
{
  cout << "0" << endl;
  return_test1();

  cout << "1" << endl;
  Test &&t1 = return_test1();
  cout << "1 " << "m_i = " << t1.m_i << " copy = " << t1.m_copy << endl;

  cout << "2" << endl;
  // t2引用内存被释放
  Test &&t2 = return_test2();
  cout << "2 " << "m_i = " << t2.m_i << " copy = " << t2.m_copy << endl;

  cout << "3" << endl;
  Test &&t3 = return_test3();
  cout << "3 " << "m_i = " << t3.m_i << " copy = " << t3.m_copy << endl;

  cout << "end" << endl;

  return 0;
}
