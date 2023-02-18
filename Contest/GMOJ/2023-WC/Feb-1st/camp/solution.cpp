#include <cstdio>
#include <string>

/* Constant */
const int N = 1500;
const int K = 1e5;
const long long mod = 1e9 + 7;

/* Declaration */
int main();

void Input();
void Solve();
void Output();

void InitPow();
void InitJC();
void InitP();
long long qpow(long long, long long);
long long Mod(long long);

void FileIO(std::string);

/* Definition */
long long p, rp;
int n, m;
int k;

long long pow_p[K + 5];
long long pow_rp[K + 5];

long long dp[N + 5][N + 5];
long long ans[N + 5];
long long left[N + 5][N + 5];
long long p1[N + 5];
long long sum_p[N + 5];
long long sum_p_left[N + 5][N + 5];
long long jc[K + 5];
long long ny[K + 5];

/* Definition */
int main()
{
  FileIO("camp");
  Input();
  Solve();
  Output();
  return 0;
}

void FileIO(std::string file_name)
{
  freopen((file_name + ".in").c_str(), "r", stdin);
  freopen((file_name + ".out").c_str(), "w", stdout);
}
void Input()
{
  scanf("%d%d", &n, &m);
  int _a, _b;
  scanf("%d%d", &_a, &_b);
  p = (_a * qpow(_b, mod - 2)) % mod;
  rp = Mod(1 - p);
  scanf("%d", &k);
  return;
}
void Solve()
{
  InitPow();
  InitJC();
  InitP();

  dp[0][m] = 1;
  ans[0] = 1;
  for (int j = 1; j <= m + 1; ++j)
  {
    left[0][j] = left[0][j - 1] + dp[0][j - 1];
    left[0][j] %= mod;
  }
  for (int j = 1; j <= m + 1; ++j)
  {
    sum_p_left[0][j] = sum_p_left[0][j - 1] + left[0][j] * p1[j - 1];
    sum_p_left[0][j] %= mod;
  }
  for (int i = 1; i <= n; ++i)
  {
    for (int j = 1; j <= m; ++j)
    {
      dp[i][j] = p1[m - j] * ((sum_p[j - 1] * Mod(ans[i - 1] - left[i - 1][m - j + 1])) % mod);
      dp[i][j] %= mod;
      dp[i][j] -= (p1[m - j] * sum_p_left[i - 1][j]) % mod;
      dp[i][j] = Mod(dp[i][j]);
    }
    for (int j = 1; j <= m + 1; ++j)
    {
      left[i][j] = left[i][j - 1] + dp[i][j - 1];
      left[i][j] %= mod;
    }
    for (int j = 1; j <= m + 1; ++j)
    {
      sum_p_left[i][j] = sum_p_left[i][j - 1] + (left[i][j] * p1[j - 1]) % mod;
      sum_p_left[i][j] %= mod;
    }
    for (int j = 1; j <= m; ++j)
    {
      ans[i] += dp[i][j];
      ans[i] %= mod;
    }
  }
  return;
}
void Output()
{
  printf("%lld", ans[n]);
  return;
}

void InitPow()
{
  pow_p[0] = pow_rp[0] = 1;
  for (int i = 1; i <= K; ++i)
    pow_p[i] = pow_p[i - 1] * p, pow_p[i] %= mod;
  for (int i = 1; i <= K; ++i)
    pow_rp[i] = pow_rp[i - 1] * rp, pow_rp[i] %= mod;
}
void InitJC()
{
  jc[0] = 1;
  for (int i = 1; i <= K; ++i)
    jc[i] = jc[i - 1] * i, jc[i] %= mod;
  ny[0] = 1;
  for (int i = 1; i <= K; ++i)
    ny[i] = qpow(jc[i], mod - 2);
  return;
}
void InitP()
{
  for (int i = 0; i <= m; ++i)
  {
    p1[i] = ((jc[k] * ny[i]) % mod) * ny[k - i];
    p1[i] %= mod;
    p1[i] *= pow_p[i];
    p1[i] %= mod;
    p1[i] *= pow_rp[k - i];
    p1[i] %= mod;
  }
  sum_p[0] = p1[0];
  for (int i = 1; i <= m; ++i)
  {
    sum_p[i] = sum_p[i - 1] + p1[i];
    sum_p[i] %= mod;
  }
  return;
}
long long Mod(long long _x)
{
  return (_x % mod + mod) % mod;
}
long long qpow(long long _x, long long _y)
{
  if (!_y)
    return 1;
  if (_y == 1)
    return _x;
  long long ret = qpow(_x, _y / 2) % mod;
  if (_y & 1)
    return (((ret * ret) % mod) * _x) % mod;
  else
    return (ret * ret) % mod;
  return 1;
}
