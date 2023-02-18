#include <cstdio>
#include <cstring>
#define int long long

/* Constant */
const int N = 2e3;
const int LEN = 1e3;
const int mod = 45660169;
const int base = 1145141;

/* Declaration */
signed main();
int GetHash(int, int);

/* Variable */
char tmp[N + 1];

int hash[LEN + 1];
int cnt[mod][2];
int base_pow[LEN + 1];

/* Definition */
signed main()
{
  freopen("in.txt", "r", stdin);
  base_pow[0] = 1;
  for (int i = 1; i <= LEN; ++i)
    base_pow[i] = base_pow[i - 1] * base % mod;
  int n, m, l;
  scanf("%lld%lld%lld", &n, &m, &l);
  int len;
  long long ans = 0;
  int sum;
  for (int i = 1; i <= n; ++i)
  {
    scanf("%s", tmp);
    len = strlen(tmp);
    for (int j = 1; j <= len; ++j)
      hash[j] = hash[j - 1] * base % mod + tmp[j - 1], hash[j] %= mod;
    for (int j = 1; j <= len - l + 1; ++j)
    {
      sum = GetHash(j, j + l - 1);
      if (cnt[sum][1] == i)
        continue;
      ++cnt[sum][0];
      cnt[sum][1] = i;
      if (cnt[sum][0] == m)
      {
        printf("%lld\n", sum);
        ++ans;
      }
    }
  }
  printf("%lld", ans);
  return 0;
}
int GetHash(int l, int r)
{
  return (((hash[r] - (long long)hash[l - 1] * base_pow[r - l + 1] % mod) % mod) + mod) % mod;
}
