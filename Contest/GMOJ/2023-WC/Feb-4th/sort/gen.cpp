#include <cstdio>
#include <cstdlib>
#include <ctime>

/* Constant */
const int N = 6;

/* Declaration */
int main();

/* Definition */
int main()
{
  srand(time(0));
  printf("%d\n", N);
  for (int i = 1; i <= N; ++i)
  {
    printf("%d ", rand() + 1);
  }
  return 0;
}
