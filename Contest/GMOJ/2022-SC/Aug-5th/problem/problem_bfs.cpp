#include <stdio.h>

const long long INF = 1e15;
const int MAXNUM = 100005;
const int MAXG = 1e6 + 5;

struct Graph
{
    int a;
    int b;
    int dis;
};


int g_tot;
void Bfs();
void FileIO();
int GetLen(int xx);
int Gf(int xx);
int Hb(int *a, int l);
int main();
int Max(int a, int b);
long long Min(long long a, long long b);
long long MST();
void Qsort(int l, int r);
long long Sovle();
void Split(int x);
template <typename T> void Swap(T &a, T &b);

int fa[MAXNUM];
int queue[MAXNUM];
int n;
int x[11];
bool pd[MAXNUM];
int tot_num;
int num[6];
int len;
Graph G[MAXG];

void Add(int u, int v, int w)
{
    ++g_tot;
    G[g_tot].a = u;
    G[g_tot].b = v; 
    G[g_tot].dis = w;
    return;
}

void Bfs()
{
    int head = 0;
    int tail = n;
    for (int i = 1; i <= n; ++i)
    {
        queue[i] = num[i];
        pd[num[i]] = true;
    }
    int xx, l, nxt;
    while (head < tail)
    {
        if (pd[1112])
        {
            nxt = true;
        }
        ++head;
        ++tot_num;
        xx = queue[head];
        l = GetLen(xx);
        Split(xx);
        for (int i = 1; i <= l; ++i)
        {
            for (int j = i + 1; j <= l; ++j)
            {
                Split(xx);
                if (x[i] != x[j])
                {
                    Swap(x[i], x[j]);
                    nxt = Hb(x, l);
                    Split(xx);
                    Add(xx, nxt, (((x[i] & x[j]) + (x[i] ^ x[j])) * 2));
                    Add(nxt, xx, (((x[i] & x[j]) + (x[i] ^ x[j])) * 2));
                    if (!pd[nxt])
                    {
                        pd[nxt] = true;
                        ++tail;
                        queue[tail] = nxt;
                    }
                }
            }
        }
        if (l == 2)
        {
            Split(xx);
            if (x[1] == x[2])
            {
                x[1] = -1;
                nxt = Hb(x, l);
                Split(xx);
                Add(xx, nxt, (x[2] + (x[2] & x[2]) + (x[2] ^ x[2])));
                Add(nxt, xx, (x[2] + (x[2] & x[2]) + (x[2] ^ x[2])));
                if (!pd[nxt])
                {
                    pd[nxt] = true;
                    ++tail;
                    queue[tail] = nxt;
                }
            }
        }
        int aa, bb, cc;
        for (int i = 1; i <= l; ++i)
        {
            if (l == 2)
                break;
            if (l == 1)
                break;
            Split(xx);
            aa = x[i];
            bb = x[i % l + 1];
            cc = x[(i - 2 + l) % l + 1];
            if (aa >= bb && aa <= cc)
            {
                x[i] = -1;
                nxt = Hb(x, l);
                Add(xx, nxt, (aa + (bb & cc) + (bb ^ cc)));
                Add(nxt, xx, (aa + (bb & cc) + (bb ^ cc)));
                if (!pd[nxt])
                {
                    pd[nxt] = true;
                    ++tail;
                    queue[tail] = nxt;
                }
            }
        }
        if (l == len)
        {
            continue;
        }
        for (int i = 1; i <= l + 1; ++i)
        {
            if (i > len)
                break;
            for (int j = 0; j <= 9; ++j)
            {
                if (i == l + 1 && j == 0)
                    continue;
                Split(xx);
                x[l + 1] = x[1];
                aa = j;
                bb = x[i];
                cc = x[(i - 2 + l) % l + 1];
                if (aa >= bb && aa <= cc)
                {
                    for (int k = l; k >= i; --k)
                    {
                        x[k + 1] = x[k];
                    }
                    x[i] = j;
                    nxt = Hb(x, l + 1);
                    Add(xx, nxt, (aa + (bb & cc) + (bb ^ cc)));
                    Add(nxt, xx, (aa + (bb & cc) + (bb ^ cc)));
                    if (!pd[nxt])
                    {
                        pd[nxt] = true;
                        ++tail;
                        queue[tail] = nxt;
                    }
                }
            }
        }
    }
}
void FileIO()
{
    freopen("problem.in", "r", stdin);
    freopen("problem.out", "w", stdout);
    return;
}
int GetLen(int xx)
{
    int ret = 0;
    while (xx)
    {
        xx /= 10;
        ++ret;
    }
    return ret;
}
int Gf(int xx)
{
    if (fa[xx] == xx)
        return xx;
    return fa[xx] = Gf(fa[xx]);
}
int Hb(int *a, int l)
{
    int ret = 0;
    for (int i = l; i >= 1; --i)
    {
        if (a[i] == -1)
            continue;
        ret = ret * 10 + a[i];
    }
    return ret;
}
int main()
{
    FileIO();
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &num[i]);
    }
    printf("%lld", Sovle());
    return 0;
}
int Max(int a, int b)
{
    return a > b ? a : b;
}
long long Min(long long a, long long b)
{
    return a < b ? a : b;
}
long long MST()
{
    for (int i = 1; i <= 99999; ++i)
    {
        fa[i] = i;
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = i + 1; j <= n; ++j)
        {
            Add(num[i], num[j], 0);
        }
    }
    Qsort(1, g_tot);
//    for (int i = 1; i <= g_tot; ++i)
//    {
//        printf("%d\n", G[i].dis);
//    }
    long long ret = 0;
    int k = 0;
    for (int i = 1; i <= g_tot; ++i)
    {
        if (Gf(G[i].a) != Gf(G[i].b))
        {
            G[i].a = Gf(G[i].a);
            G[i].b = Gf(G[i].b);
            fa[G[i].a] = G[i].b;
            ret += G[i].dis;
            ++k;
            if (k == tot_num - 1)
                break;
        }
    }
    return ret;
}
void Qsort(int l, int r)
{
    int i = l, j = r;
    int mid = (l + r) >> 1;
    while (i <= j)
    {
        while (G[i].dis < G[mid].dis)
            ++i;
        while (G[j].dis > G[mid].dis)
            --j;
        if (i <= j)
        {
            Swap(G[i], G[j]);
            if (mid == i)
                mid = j;
            else if (mid == j)
                mid = i;
            ++i;
            --j;
        }
    }
    if (i < r)
        Qsort(i, r);
    if (l < j)
        Qsort(l, j);
    return;
}
long long Sovle()
{
    for (int i = 1; i <= n; ++i)
    {
        len = Max(len, GetLen(num[i]));
    }
    Bfs();
    return MST();
}
void Split(int xx)
{
    int ll = 0;
    while (xx)
    {
        ++ll;
        x[ll] = xx % 10;
        xx /= 10;
    }
    return;
}
template <typename T> void Swap(T &a, T &b)
{
    T tmp = a;
    a = b;
    b = tmp;
    return;
}
