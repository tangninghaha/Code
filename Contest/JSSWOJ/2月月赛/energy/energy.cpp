#include <cstdio>

/* Constant */
const int N = 5e5 + 5;

/* Declaration */
int main();
long long Sovle(const int, long long);
int Mod(int, const int mod_num);
long long Min(long long, long long);

/* Variable */
long long a[N + 1];
bool vis[N + 1];
long long num[N + 1];

/* Definition */
int main()
{
  freopen("energy.in", "r", stdin);
  freopen("energy.out", "w", stdout); 
  int n, k;
  scanf("%d%d", &n, &k);
  long long sum = 0;
  for (int i = 1; i <= n; ++i)
  {
    scanf("%lld", &a[i]);
    sum += a[i];
  }
  long long ans = 0;
  sum /= n;
  for (int i = 1; i <= n; ++i)
  {
    if (vis[i])
      continue;
    vis[i] = true;
    int j = Mod(i + k + 1, n);
    int cnt = 1;
    num[1] = a[i];
    while (!vis[j])
    {
      vis[j] = true;
      ++cnt;
      num[cnt] = a[j];
      j = Mod(j + k + 1, n);
    }
    ans += Sovle(cnt, sum);
  }
  printf("%lld", ans);
  return 0;
}
long long Sovle(const int n, long long pur)
{
  int left = n - 2;
  left = Mod(left, n); 
  int right = 2;
  int len = 2;
  long long ret = 0;
  long long tmp = 0;
  for (int i = 1; i <= n; ++i)
  {
    left += 2;
    left = Mod(left, n);
    --len;
    if (len == 0)
    {
      --left;
      ++right;
      left = Mod(left, n);
      right = Mod(right, n);
      ++len; 
    } 
    if (num[i] >= pur)
      continue;
    else
    {
      while (num[i] < pur)
      {
        if (num[left] > pur)
        {
          tmp = Min(num[left] - pur, pur - num[i]);
          num[i] += tmp;
          num[left] -= tmp;
          ret += tmp * len;
        }
        else if (num[right] > pur)
        {
          tmp = Min(num[right] - pur, pur - num[i]);
          num[i] += tmp;
          num[right] -= tmp;
          ret += tmp * len;
        }
        else
        {
          --left;
          ++right;
          left = Mod(left, n);
          right = Mod(right, n);
          ++len;
        }
      }
    }
  }
  return ret;
}
int Mod(int x, const int n)
{
  return ((x - 1) % n + n) % n + 1;
}
long long Min(long long _a, long long _b)
{
  return _a < _b ? _a : _b;
}
