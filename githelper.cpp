#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>

using std::string;

/* Declaration */
int main();
void Init();
void Push();
void AddRemote();
void Commit(string);

/* Definition */
void Init()
{
  system("git init");
}
void Pull()
{
  system("git pull origin");
  return;
}
void AddRemote()
{
  system("git remote add origin git@github.com:tangninghaha/Code.git");
  return;
}
void Push()
{
  system("git push -u origin");
  return;
}
void Commit(string mes)
{
  system("git add .");
  system(("git commit -m " + mes).c_str());
  return;
}
int main()
{
  while (true)
  {
    int x;
    scanf("%d", &x);
    if (x == 1)
      Init();
    else if (x == 2)
      AddRemote();
    else if (x == 3)
    {
      string mes;
      std::cin >> mes;
      Commit(mes);
    }
    else if (x == 4)
    {
      Push();
    }
    else if (!x)
    {
      return 0;
    }
  }
}
