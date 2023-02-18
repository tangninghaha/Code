#include <cstdio>

/* Constant */
const int N = 3;
const int M = 10;

/* Declaration */
int main();

void Draw(int, int);
void ChosK(int);

long long C(int, int);

/* Variable */
int n, m, k;
long long jc[M + 1];
long double base, ans;

bool draw_vis[M + 1];
int color[N + 1][N + 1];
bool color_chos[M + 1];
int twom[N * 2 + 1];

/* Definition */
int main()
{
  twom[0] = 1;
  for (int i = 1; i < N * 2; ++i)
  {
    twom[i] = twom[i - 1] << 1;
  }
  jc[0] = 1;
  for (int i = 1; i <= 10; ++i)
    jc[i] = jc[i - 1] * i;
  scanf("%d%d%d", &n, &m, &k);
  base = 1 / double((long long)C(m, n * n) * C(m, k) * jc[n * n]);
  Draw(1, 1);
  printf("%Lf", ans);
  return 0;
}

long long C(int m, int n)
{
  long long ret = jc[m];
  ret /= jc[n];
  ret /= jc[m - n];
  return ret;
}
void Draw(int _x, int _y)
{
  if (_x == n + 1)
  {
    ChosK(1);
  }
  for (int i = 1; i <= m; ++i)
  {
    if (!draw_vis[i])
    {
      color[_x][_y] = i;
      draw_vis[i] = true;
      if (_y != n)
        Draw(_x, _y + 1);
      else
        Draw(_x + 1, 1);
      draw_vis[i] = false;
    }
  }
}
void ChosK(int _x)
{
  if (_x > k)
  {
    bool pd;
    int cnt = 0;
    for (int i = 1; i <= n; ++i)
    {
      pd = true;
      for (int j = 1; j <= n; ++j)
      {
        if (!color_chos[color[i][j]])
        {
          pd = false;
          break;
        }
      }
      if (pd)
        ++cnt;
    }
    for (int i = 1; i <= n; ++i)
    {
      pd = true;
      for (int j = 1; j <= n; ++j)
      {
        if (!color_chos[color[j][i]])
        {
          pd = false;
          break;
        }
      }
      if (pd)
        ++cnt;
    }
    ans += twom[cnt] * base;
    return;
  }
  for (int i = 1; i <= m; ++i)
  {
    if (!color_chos[i])
    {
      color_chos[i] = true;
      ChosK(_x + 1);
      color_chos[i] = false;
    }
  }
}
