#include <cstdio>
#include <cstdlib>
#include <ctime>

int main()
{
  srand(time(0));
  int n = 8, m = 10;
  printf("%d %d\n", n, m);
  int t1, t2;
  for (int i = 1; i <= n; ++i)
  {
    t1 = rand() % m + 1;
    t2 = rand() % m + 1;
    while (t1 == t2)
      t2 = rand() % m + 1;
    printf("%d %d\n", t1, t2);
  }
}
