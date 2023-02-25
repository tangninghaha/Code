#include <cstdio>

/* Constant */
const int N = 20;

/* Class */
class REC
{
  public:
    int sum;
    long long num;
    int sta;
};
bool operator<(const REC& _a, const REC& _b)
{
  if (_a.sum == _b.sum)
    return _a.num < _b.num;
  return _a.sum < _b.sum;
}

/* Declaration */
int main();
void Dfs(int);
void Init();
template <typename T> void Qsort(int, int, T*);
template <typename T> void Swap(T&, T&);
void print(long long);

/* Variable */
int n, t;
int half_n;
int twom[N + 1];
int a[N + 1];
long long c[N][N];
bool vis[N + 1];
REC rec[3628801];
int rec_tot;
int stack[11];
int temp[N + 1];
int ans[N + 1];

/* Definition */
void Update_ans(long long _x, long long _y)
{
  int top = 0;
  while (_x)
  {
    stack[++top] = _x % 10;
    _x /= 10;
  }
  int len = 0;
  for (int i = top; i >= 1; --i)
    temp[++len] = stack[i];
  while (_y)
  {
    temp[++len] = _y % 10;
    _y /= 10;
  }
  for (int i = 1; i <= n; ++i)
  {
    if (ans[i] < temp[i] && ans[i])
    {
      return;
    }
    else if (temp[i] < ans[i])
      break;
  }
  for (int i = 1; i <= n; ++i)
    ans[i] = temp[i];
  return;
}
template <typename T> void Qsort(int l, int r, T* _a)
{
  int i = l, j = r;
  T mid = _a[l + r >> 1];
  while (i <= j)
  {
    while (_a[i] < mid)
      ++i;
    while (mid < _a[j])
      --j;
    if (i <= j)
    {
      Swap(_a[i], _a[j]);
      ++i;
      --j;
    }
  }
  if (i < r)
    Qsort(i, r, _a);
  if (l < j)
    Qsort(l, j, _a);
  return;
}
template <typename T> void Swap(T& _a, T& _b)
{
  T tmp = _a;
  _a = _b;
  _b = tmp;
  return;
}
void Init()
{
  c[0][0] = 1;
  for (int i = 1; i < 20; ++i)
  {
    for (int j = 0; j <= i; ++j)
    {
      c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
    }
  }
  twom[0] = 1;
  for (int i = 1; i <= 20; ++i)
  {
    twom[i] = twom[i - 1] << 1;
  }
  return;
}
int main()
{
  freopen("easy.in", "r", stdin);
  freopen("easy.out", "w", stdout);
  Init();
  scanf("%d%d", &n, &t);
  while (n != 0 && t != 0)
  {
    if (n & 1)
    {
      half_n = n / 2 + 1;
      Dfs(1);
      int first = rec_tot;
      --half_n;
      Dfs(1);
      Qsort(1, first, rec);
      Qsort(first + 1, rec_tot, rec);
      int lbound, rbound, mid, pur;
      int x = 0;
      rec[0].sum = -1;
      for (int i = 1; i <= first; ++i)
      {
        if (rec[i].sum > t)
          break;
        if (rec[i].sum != rec[i - 1].sum)
        {
          lbound = first + 1, rbound = rec_tot;
          pur = t - rec[i].sum;
          x = n + 1;
          while (lbound <= rbound)
          {
            mid = lbound + rbound >> 1;
            if (rec[mid].sum < pur)
            {
              lbound = mid + 1;
            }
            else if (rec[mid].sum > pur)
            {
              rbound = mid - 1;
            }
            else
            {
              x = mid;
              rbound = mid - 1;
            }
          }
        }
        if (x == n + 1)
          continue;
        for (int j = x; j <= rec_tot; ++j)
        {
          if (rec[j].sum != pur)
            break;
          if ((rec[j].sta ^ rec[i].sta) == twom[n] - 1)
          {
            Update_ans(rec[i].num, rec[j].num);
          }
        }
      }
    }
    else
    {
      half_n = n / 2;
      Dfs(1);
      Qsort(1, rec_tot, rec);
      int lbound, rbound, mid, pur;
      int x = 0;
      rec[0].sum = -1;
      for (int i = 1; i <= rec_tot; ++i)
      {
        if (rec[i].sum > t)
          break;
        if (rec[i].sum != rec[i - 1].sum)
        {
          lbound = 1, rbound = rec_tot;
          pur = t - rec[i].sum;
          x = n + 1;
          while (lbound <= rbound)
          {
            mid = lbound + rbound >> 1;
            if (rec[mid].sum < pur)
            {
              lbound = mid + 1;
            }
            else if (rec[mid].sum > pur)
            {
              rbound = mid - 1;
            }
            else
            {
              x = mid;
              rbound = mid - 1;
            }
          }
        }
        if (x == n + 1)
          continue;
        for (int j = x; j <= rec_tot; ++j)
        {
          if (rec[j].sum != pur)
            break;
          if ((rec[j].sta ^ rec[i].sta) == twom[n] - 1)
          {
            Update_ans(rec[i].num, rec[j].num);
          }
        }
      }
    }
    for (int i = 1; i <= n; ++i)
    {
      printf("%d", ans[i]);
      if (i != n)
        printf(" ");
    }
    printf("\n");
    for (int i = 1; i <= n; ++i)
    {
      ans[i] = 0;
    }
    rec_tot = 0;
    scanf("%d%d", &n, &t);
  }
  return 0;
}
void Dfs(int _x)
{
  if (_x > half_n)
  {
    ++rec_tot;
    int sum = 0;
    long long num = 0;
    int sta = 0;
    for (int i = 1; i <= half_n; ++i)
    {
      sum += c[n - 1][i - 1] * a[i];
      num = num * 10 + a[i];
      sta += twom[a[i] - 1];
    }
    rec[rec_tot].sum = sum;
    rec[rec_tot].num = num;
    rec[rec_tot].sta = sta;
    return;
  }
  for (int i = 1; i <= n; ++i)
  {
    if (!vis[i])
    {
      a[_x] = i;
      vis[i] = true;
      Dfs(_x + 1);
      vis[i] = false;
    }
  }
}
