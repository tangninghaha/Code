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
void Pull()
{
  system("git pull origin");
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
  	system("cls");
  	printf("[1]Pull\n[2]Push\n[3]Commit\n");
    int x;
    scanf("%d", &x);
    if (x == 1)
      Pull();
    else if (x == 2)
      Push();
    else if (x == 3)
    {
      string mes;
      printf("Message: "); 
      std::cin >> mes;
      Commit(mes);
    }
    else if (!x)
    {
      return 0;
    }
    system("pause");
  }
}
