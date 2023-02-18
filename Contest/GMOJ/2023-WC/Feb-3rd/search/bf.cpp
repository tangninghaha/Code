#include <cstdio>
#include <cstring>

/* Constant */
const int N = 2e3;
const int LEN = 1e3;

/* Declaration */
int main();

/* Variable */
char cha[N + 1][LEN + 1];
int len[N + 1];
bool vis[N + 1][LEN + 1];

/* Definition */
int main()
{
  int n, m, l;
  scanf("%d%d%d", &n, &m, &l);
  for (int i = 1; i <= n; ++i)
  {
    scanf("%s", cha[i]);
    len[i] = strlen(cha[i]);
  }
  int cnt;
  long long ans = 0;
  bool th_line;
  for (int i = 1; i <= n; ++i)
  {
    for (int j = 0; j < len[i] - l + 1; ++j)
    {
      if (vis[i][j])
        continue;
      cnt = 0;
      for (int k = i + 1; k <= n; ++k)
      {
        th_line = false;
        for (int x = 0; x < len[k] - l + 1; ++x)
        {
          bool pd = false;
          for (int y = 0; y < l; ++y)
          {
            if (cha[k][x + y] != cha[i][j + y])
            {
              pd = true;
              break;
            }
          }
          if (!pd && !th_line)
            ++cnt, th_line = true;
          if (!pd)
            vis[k][x] = true;
        }
      }
      if (cnt + 1 >= m)
        ++ans;
      for (int k = j + 1; k < len[i] - l + 1; ++k)
      {
        bool pd = false;
        for (int x = 0; x < l; ++x)
        {
          if (cha[i][j + x] != cha[i][k + x])
          {
            pd = true;
            break;
          }
        }
        if (!pd)
          vis[i][k] = true;
      }
    }
  }
  printf("%lld", ans);
  return 0;
}
