#include <cstdio>

/* Constant */
const int MAXN = 1e5 + 5;
const int LEN = 14;
const long long LIM = 1e14;
const int LIMNUM = 14;

/* Class */
struct HighNum
{
    HighNum();
    long long a[LEN];
    int len;
    void Read();
    void Print();
};
struct Graph
{
    int head[MAXN];
    int nxt[MAXN * 2];
    int to[MAXN * 2];
    int tot;
    void Add(int, int);
};

/* Declaration */
HighNum operator+(const HighNum&, const HighNum&);
HighNum operator*(const HighNum&, const int&);
int Abs(int);
int main();
int Read();
void Dfs(int, int);
int start_num[MAXN];
int to_num[MAXN];
int is_start_num[MAXN];
int is_to_num[MAXN];
int bian[MAXN * 2];
int Max(int, int);

/* Variable */
HighNum ans;
Graph G;
HighNum w[MAXN];

/* Definition */
int main()
{
    G.tot = 1;
    int n, m;
    n = Read();
    m = Read();
    int s;
    for (int i = 1; i <= m; ++i)
    {
        s = Read();
        ++is_start_num[s];
    }
    for (int i = 1; i <= m; ++i)
    {
        s = Read();
        ++is_to_num[s];
    }
    int _u, _v;
    for (int i = 1; i < n; ++i)
    {
        _u = Read();
        _v = Read();
        w[i].Read();
        G.Add(_u, _v);
        G.Add(_v, _u);
    }
    Dfs(1, 0);
    for (int i = 1; i < n; ++i)
    {
        ans = ans + w[i] * Abs(start_num[bian[i * 2]] - to_num[bian[i * 2]]);
    }
    ans.Print();
    return 0;
}
void Dfs(int _x, int fa)
{
    start_num[_x] = is_start_num[_x];
    to_num[_x] = is_to_num[_x];
    for (int i = G.head[_x]; i; i = G.nxt[i])
    {
        if (G.to[i] != fa)
        {
            bian[i] = G.to[i];
            bian[i ^ 1] = G.to[i];
            Dfs(G.to[i], _x);
            start_num[_x] += start_num[G.to[i]];
            to_num[_x] += to_num[G.to[i]];
        }
    }
}
int Abs(int _x)
{
    return _x < 0 ? -_x : _x;
}
HighNum operator+(const HighNum& _a, const HighNum& _b)
{
    HighNum ret;
    ret.len = Max(_a.len, _b.len);
    for (int i = 1; i <= ret.len; ++i)
    {
        ret.a[i] = _a.a[i] + _b.a[i];
        if (ret.a[i] >= LIM)
        {
            ret.a[i + 1] += ret.a[i] / LIM;
            ret.a[i] %= LIM;
            if (i == ret.len)
            {
                ++ret.len;
            }
        }
    }
    return ret;
}
HighNum operator*(const HighNum& _a, const int& _b)
{
    HighNum ret;
    ret.len = _a.len;
    for (int i = 1; i <= ret.len; ++i)
    {
        ret.a[i] += _a.a[i] * _b;
        if (ret.a[i] >= LIM)
        {
            ret.a[i + 1] += ret.a[i] / LIM;
            ret.a[i] %= LIM;
            if (i == ret.len)
            {
                ++ret.len;
            }
        }
    }
    return ret;
}
HighNum::HighNum()
{
    len = 0;
    for (int i = 0; i < LEN; ++i)
    {
        a[i] = 0;
    }
}
int Read()
{
    int ret = 0;
    char tmp = getchar();
    while (tmp < '0' || tmp > '9')
        tmp = getchar();
    while (tmp >= '0' && tmp <= '9')
    {
        ret = (ret << 1) + (ret << 3) + tmp - '0';
        tmp = getchar();
    }
    return ret;
}
void HighNum::Read()
{
    len = 1;
    char tmp = getchar();
    while (tmp < '0' || tmp > '9')
    {
        tmp = getchar();
    }
    long long temp;
    int k = 0;
    while (tmp >= '0' && tmp <= '9')
    {
        a[len] = (a[len] << 1) + (a[len] << 3) + tmp - 48;
        ++k;
        if (a[len] >= LIM)
        {
            k = 0;
            a[len + 1] += a[len] / LIM;
            a[len] %= LIM;
            ++len;
        }
        tmp = getchar();
    }
    for (int x = 1; x <= len; ++x)
    {
        temp = 0;
        for (int i = 1; i <= LIMNUM; ++i)
        {
            if (x == len && i > k)
                break;
            temp = (temp << 1) + (temp << 3) + a[x] % 10;
            a[x] /= 10;
        }
        a[x] = temp;
    }
    return;
}
void HighNum::Print()
{
    printf("%lld", a[len]);
    for (int i = len - 1; i >= 1; --i)
    {
        printf("%14lld", a[i]);
    }
}
int Max(int _a, int _b)
{
    return _a > _b ? _a : _b;
}
void Graph::Add(int _u, int _v)
{
    ++tot;
    nxt[tot] = head[_u];
    to[tot] = _v;
    head[_u] = tot;
    return;
}
