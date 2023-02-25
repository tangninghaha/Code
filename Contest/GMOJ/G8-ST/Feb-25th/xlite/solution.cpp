#include <cstdio>

/* Constant */
const int N = 50;
const int INF = 1 << 29;

/* Declaration */
int main();
void Dfs(int, long long, int);
long long lowbit(long long);

/* Variable */
int n, l;
char tmp[N + 1];
long long ostatus;
long long fork;
int ans = INF, min_times = INF;

/* Definition */
int main()
{
  freopen("xlite.in", "r", stdin);
  freopen("xlite.out", "w", stdout);
  scanf("%d%d", &n, &l);
  scanf("%s", tmp + 1);
  for (int i = 1; i <= n; ++i)
    ostatus = (ostatus << 1) + tmp[i] - '0';
  scanf("%s", tmp + 1);
  for (int i = 1; i <= l; ++i)
    fork = (fork << 1) + tmp[i] - '0';
  Dfs(1, ostatus, 0);
  printf("%d", min_times);
  return 0;
}
void Dfs(int x, long long status, int times)
{
  if (x + l - 1 > n)
  {
    int cnt = 0;
    while (status)
      status -= lowbit(status), ++cnt;
    if (cnt > ans)
      return;
    if (cnt < ans)
    {
      ans = cnt;
      min_times = times;
      return;
    }
    if (min_times > times)
      min_times = times;
    return;
  }
  Dfs(x + 1, status ^ (fork << (n - x - l + 1)), times + 1);
  Dfs(x + 1, status, times);
  return;
}
long long lowbit(long long _x)
{
  return _x & -_x;
}
