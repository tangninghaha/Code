#include <cstdio>

/* Constant */
const int N = 100;
const int INF = 1 << 29;

/* Declaration */
int main();
int Min(int, int);

/* Variable */
int a[4][N + 1][N + 1];
int num[2][4];

/* Definition */
int main()
{
  int n;
  scanf("%d", &n);
  for (int k = 0; k < 4; ++k)
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        scanf("%1d", &a[k][i][j]);
  for (int k = 0; k < 4; ++k)
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        if (((i + j) & 1))
        {
          if (!a[k][i][j])
            ++num[0][k];
          else
            ++num[1][k];
        }
        else
        {
          if (a[k][i][j])
            ++num[0][k];
          else
            ++num[1][k];
        }

  int ans = INF;
  for (int a1 = 0; a1 < 4; ++a1)
  {
    for (int a2 = 0; a2 < 4; ++a2)
    {
      if (a1 == a2)
        continue;
      for (int a3 = 0; a3 < 4; ++a3)
      {
        if (a1 == a3 || a2 == a3)
          continue;
        for (int a4 = 0; a4 < 4; ++a4)
        {
          if (a1 == a4 || a2 == a4 || a3 == a4)
            continue;
          ans = Min(ans, num[0][a1] + num[1][a2] + num[1][a3] + num[0][a4]);
          ans = Min(ans, num[1][a1] + num[0][a2] + num[0][a3] + num[1][a4]);
        }
      }
    }
  }
  printf("%d", ans);
  return 0;
}
int Min(int _a, int _b)
{
  return _a < _b ? _a : _b;
}
