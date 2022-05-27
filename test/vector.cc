#include <vector>

using std::vector;

int main()
{
  vector<int>  a; 
  a.push_back(10);
  a.push_back(20);
  a.push_back(30);
  a.push_back(40);
  a.push_back(50);
  for (auto i = a.begin(); i !=a.end();)
  {
    if (*i == 20)
    {
      i = a.insert(i, 18); //现在i指向18　　　　　　　　　　　　　　
      ++i; //现在i指向20，即判断条件里的20
      i=a.erase(i); //现在i指向30.即原本20的后面
    }
    else
      ++i;
  }
  for (auto i = a.begin(); i != a.end();++i)
  {
    cout << *i << endl;
  }
  system("pause");


  return 0;
}
