#include <cstdio>

/* Constant */
const int MAXN = 2e5 + 5;
const int INF = 1e8 + 5;

/* Class */
struct Node
{
    int num1;
    int num2;
    int bh;
};
struct Heap
{
    Node a[MAXN];
    int rk[MAXN];
    int size;

    void Add(Node);
    Node Pop();
    void Up(int);
    void Down(int);
};
struct Graph
{
    int head[MAXN];
    int nxt[MAXN];
    int to[MAXN];
    int tot;
    void Add(int, int);
};

/* Declaration */
int main();
int Sovle(int, int, bool);

int GetMin(int, int, int);

int Min(int, int);

//void Qsort(int, int);
template<typename T> void Swap(T&, T&);

bool operator< (const Node&, const Node&);

/* Variable */
Graph G;
Heap H;
int ans_tot;
Node ans[MAXN];
int minn[MAXN][20][2];
int twom[20];
int log_2[MAXN];
int rk[MAXN];

int p[MAXN];

/* Definition */
void Heap::Up(int _x)
{
    int nxt = _x / 2;
    while (nxt && a[_x] < a[nxt])
    {
        Swap(a[nxt], a[_x]);
        rk[a[_x].bh] = _x;
        rk[a[nxt].bh] = nxt;
        _x = nxt;
        nxt = _x / 2;
    }
    return;
}
void Heap::Down(int _x)
{
    int nxt = _x * 2;
    while ((nxt <= size && a[nxt] < a[_x]) || (nxt + 1 <= size && a[nxt + 1] < a[_x]))
    {
        if (a[nxt + 1] < a[nxt] && nxt + 1 <= size)
            ++nxt;
        Swap(a[_x], a[nxt]);
        rk[a[_x].bh] = _x;
        rk[a[nxt].bh] = nxt;
        _x = nxt;
        nxt = _x * 2;
    }
    return;
}
Node Heap::Pop()
{
    Swap(a[1], a[size]);
    rk[a[1].bh] = 1;
    rk[a[size].bh] = -1;
    --size;
    Down(1);
    return a[size + 1];
}
void Heap::Add(Node _x)
{
    ++size;
    a[size] = _x;
    rk[_x.bh] = size;
    Up(size);
    return;
}

int main()
{
    freopen("seq.in", "r", stdin);
    freopen("seq.out", "w", stdout);
    twom[0] = 1;
    for (int i = 1; i <= 19; ++i)
    {
        twom[i] = twom[i - 1] << 1;
    }
    int n;
    scanf("%d", &n);
    log_2[1] = 0;
    for (int i = 2; i <= n; ++i)
    {
        log_2[i] = log_2[i / 2] + 1;
    }
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &p[i]);
        rk[p[i]] = i;
    }

    for (int i = 1; i <= n; ++i)
    {
        minn[i][0][i & 1] = p[i];
        minn[i][0][!(i & 1)] = INF;
    }
    for (int k = 1; k <= log_2[n] + 1; ++k)
    {
        for (int i = 1; i <= n; ++i)
        {
            if (i + twom[k - 1] > n)
                continue;
            minn[i][k][0] = Min(minn[i][k - 1][0], minn[i + twom[k - 1]][k - 1][0]);
            minn[i][k][1] = Min(minn[i][k - 1][1], minn[i + twom[k - 1]][k - 1][1]);
        }
    }

    Sovle(1, n, 0);

    int now = 1;
    printf("%d %d ", ans[1].num1, ans[1].num2);
    Node ret;
    for (int i = 2; i <= n / 2; ++i)
    {
        for (int j = G.head[now]; j; j = G.nxt[j])
        {
            H.Add(ans[G.to[j]]);
        }
        ret = H.Pop();
        now = ret.bh;
        printf("%d %d ", ret.num1, ret.num2);
    }
    
//    Qsort(1, n / 2);
    return 0;
}
int Sovle(int l, int r, bool flag)
{
    if (l > r)
        return -1;
    ++ans_tot;
    ans[ans_tot].num1 = GetMin(l, r, !flag);
    int tmp1 = rk[ans[ans_tot].num1];
    ans[ans_tot].num2 = GetMin(tmp1, r, flag);
    int tmp2 = rk[ans[ans_tot].num2];
    ans[ans_tot].bh = ans_tot;
    int x = ans_tot;

    int ret;
    ret = Sovle(l, tmp1 - 1, flag);
    if (ret != -1)
        G.Add(x, ret);
    ret = Sovle(tmp1 + 1, tmp2 - 1, !flag);
    if (ret != -1)
        G.Add(x, ret);
    ret = Sovle(tmp2 + 1, r, flag);
    if (ret != -1)
        G.Add(x, ret);
//    printf("%d %d ", ret.num1, ret.num2);
    return x;
}
int GetMin(int l, int r, int type)
{
    int k = log_2[r - l + 1];
    return Min(minn[l][k][type], minn[r - twom[k] + 1][k][type]);
}
//void Qsort(int l, int r)
//{
//    const Node mid = ans[(l + r) >> 1];
//    int i = l, j = r;
//    while (i <= j)
//    {
//        while (ans[i] < mid)
//            ++i;
//        while (mid < ans[j])
//            --j;
//        if (i <= j)
//        {
//            Swap(ans[i], ans[j]);
//            ++i;
//            --j;
//        }
//    }
//    if (i < r)
//        Qsort(i, r);
//    if (l < j)
//        Qsort(l, j);
//    return;
//}
template<typename T> void Swap(T& _a, T& _b)
{
    T t = _a;
    _a = _b;
    _b = t;
    return;
}
bool operator< (const Node& _a, const Node& _b)
{
    return _a.num1 < _b.num1;
}
int Min(int _a, int _b)
{
    return _a < _b ? _a : _b;
}
void Graph::Add(int _u, int _v)
{
    ++tot;
    nxt[tot] = head[_u];
    to[tot] = _v;
    head[_u] = tot;
    return;
}
