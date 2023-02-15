#include <cstdio>

/* Constant */
const int N = 1000;

/* Declaration */
int main();

/* Variable */
int a[N + 1];

/* Definition */
int main()
{
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
  {
    scanf("%d", &a[i]);
  }
}
