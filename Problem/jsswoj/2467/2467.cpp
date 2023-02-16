#include <cstdio>

/* Constant */
const int N = 1000;
const int X = 11;
const int mod = 998244353;

/* Declaration */
int main();
void Add(int, int);
void Del(int, int);

/* Variable */
int a[N + 1];
int num[X];
int f[N + 1][X];
int len;

/* Definition */
int main()
{
  int n;
  int sum = 0;
  while (scanf("%1d", &a[++n]) != EOF)
  {
    sum += a[n];
    sum %= X;
  }
  --n;
  f[0][0] = 1;
  for (int i = 1; i <= n; ++i)
  {
    Add(n, a[i]);
  }
  int aa, bb;
  int s0 = sum * 6 % X;
  int s1 = s0;
  for (int i = 1; i <= n; ++i)
  {
    if (i & 1)
      aa = n / 2 - i / 2, bb = s0;
    else
      aa = (n + 1) / 2 - (i + 1) / 2, bb = s1;
    for (int j = 9; j >= 0; --j)
    {
      if (!num[j])
        continue;
      Del(n, j);
      if (!f[aa][bb])
      {
        Add(n, j);
        continue;
      }
      printf("%d", j);
      if (i & 1)
        s1 = (s1 + X - j) % X;
      else
        s0 = (s0 + X - j) % X;
      break;
    }
  }
}
void Add(int n, int _x)
{
  for (int i = len; i >= 0; --i)
  {
    for (int j = 0; j <= 10; ++j)
    {
      (f[i + 1][(j + _x) % X] += f[i][j]) %= mod;
    }
  }
  ++len;
  ++num[_x];
  return;
}
void Del(int n, int _x)
{
  for (int i = 0; i <= len; ++i)
  {
    for (int j = 0; j <= 10; ++j)
    {
      (f[i + 1][(j + _x) % X] += mod - f[i][j]) %= mod;
    }
  }
  --len;
  --num[_x];
  return;
}
