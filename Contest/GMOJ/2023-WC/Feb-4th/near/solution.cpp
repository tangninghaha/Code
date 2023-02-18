#include <cstdio>
#include <bitset>

/* Constant */
const int N = 1e6;

/* Class */
class Link
{
  public:
    int left;
    int right;
    int bh;
};

/* Definition */
void Delete(Link&);

int main();

/* Variable */
Link l[N + 1];
int t[N * 2 + 1];
int p[N + 1], b[N + 1];
int rk[N + 1];

/* Definition */
int main()
{
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
  {
    scanf("%d%d", &p[i], &b[i]);
  }
  for (int i = 1; i <= n; ++i)
  {
    t[p[i]] = i;
  }
  int pre;
  pre = 0;
  long long ans = 0;
  int cnt = 0;
  for (int i = 1; i <= m; ++i)
  {
    if (!t[i])
      continue;
    if (pre != 0)
    {
      ans += b[t[pre]] ^ b[t[i]];
    }
    l[cnt].right = cnt + 1;
    ++cnt;
    l[cnt].left = cnt - 1;
    l[cnt].bh = t[i];
    rk[t[i]] = cnt;
    pre = i;
  }
  l[0].right = 0;
  long long sum = ans;
  for (int i = n; i >= 2; --i)
  {
    if (l[rk[i]].left != 0)
      ans -= b[i] ^ b[l[l[rk[i]].left].bh];
    if (l[rk[i]].right != 0)
      ans -= b[i] ^ b[l[l[rk[i]].right].bh];
    if (l[rk[i]].left != 0 && l[rk[i]].right != 0)
      ans += b[l[l[rk[i]].left].bh] ^ b[l[l[rk[i]].right].bh];
    Delete(l[rk[i]]);
    sum ^= ans;
  }
  printf("%lld", sum);
  return 0;
}
void Delete(Link& _x)
{
  l[_x.left].right = _x.right;
  l[_x.right].left = _x.left;
  return;
}
