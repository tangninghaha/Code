#include <cstdio>
#include <cstdlib>
#include <ctime>

/* Constant */
const int N = 100;

/* Declaration */
int main();

/* Variable */
bool pd[N + 1];

/* Definition */
int main()
{
  srand(time(0));
  printf("%d\n", N);
  int t;
  for (int i = 1; i <= N; ++i)
  {
    t = rand() % N + 1;
    while (pd[t])
      t = rand() % N + 1;
    pd[t] = true;
    printf("%d ", t);
  }
}
