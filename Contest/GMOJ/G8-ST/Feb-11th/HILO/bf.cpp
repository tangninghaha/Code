#include <cstdio>

/* Constant */
const int N = 2e5;

/* Declaration */
int main();

/* Variable */
int a[N + 1];
int res[N + 1];

/* Definition */
int main()
{
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
  {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i <= n; ++i)
  {
    res[i] = -1;
  }
  int pre;
  for (int i = 0; i <= n; ++i)
  {
    double x = i + 0.5;
    for (int j = 1; j <= n; ++j)
    {
      bool pd = false;
      for (int k = 1; k < j; ++k)
      {
        if (a[k] < a[j] && res[k] == 0)
        {
          pd = true;
          break;
        }
        if (a[k] > a[j] && res[k] == 1)
        {
          pd = true;
          break;
        }
      }
      if (pd)
      {
        res[j] = -1;
        continue;
      }
      if (a[j] > x)
        res[j] = 0;
      else
        res[j] = 1;
    }
//    for (int j = 1; j <= n; ++j)
//      if (res[j] != -1)
//        printf("%s", res[j] == 0 ? "HI" : "LO");
//    printf("\n");
    pre = -1;
    int ans = 0;
    for (int j = 1; j <= n; ++j)
    {
      if (res[j] == -1)
        continue;
      if (pre == 0 && res[j] == 1)
        ++ans;
      pre = res[j];
    }
    printf("%d\n", ans);
  }
  return 0;
}
