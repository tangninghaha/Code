#include <stdio.h>
#include <cmath>
#include <string.h>
#define INF 707406378
#define T 1000000
const int MAXN = 501, MAXM = 20005;
struct PF
{
    int a;
    int b;
};
bool operator<(PF &a, PF &b);
bool operator>(PF &a, PF &b);
struct InputData
{
    bool x;
    int num;
};
InputData Read();
struct Edge
{
    int head[MAXN];
    int nxt[MAXM];
    int to[MAXM];
    InputData dis[MAXM];
    int tot;
    void Add(int x, int y, InputData z);
};
int dis[501][10005];
int queue[1000001][2];
bool vis[501][10005];
PF way[MAXM];
int way_tot;
PF tmp[MAXM];
int tmp_tot;
Edge G;
void FileIO();
void Swap(PF &a, PF &b);
void Qsort(int l, int r);
void GetAns(int a, int b);
int minn[MAXN], maxn[MAXN];
int min(int a, int b);
int max(int a, int b);
void BellmanFord(int st);
int n, m;

void FileIO()
{
    freopen("travel.in", "r", stdin);
//    freopen("travel.out", "w", stdout);
    return;
}
int main()
{
    G.tot = 1;
    scanf("%d%d", &n, &m);
    int u, v;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &u, &v);
        G.Add(u, v, Read());
    }
    int q;
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i)
    {
        scanf("%d%d", &u, &v);
        GetAns(u, v);
    }
    return 0;
}

void BellmanFord(int st)
{
    int head = 0, tail = 1;
    dis[st][0] = 0;
    queue[1][0] = st;
    queue[1][1] = 0;
    int p, diss;
    while (head < tail)
    {
        ++head;
		if (head == T)
		{
			head = 1;
		}
        p = queue[head][0];
        diss = queue[head][1];
		vis[p][diss] = false;
        for (int i = G.head[p]; i; i = G.nxt[i])
        {
            if (G.dis[i].x)
            {
                if(dis[p][diss] < dis[G.to[i]][diss + 1] && diss + 1 <= m)
                {
					if (vis[G.to[i]][diss + 1])
 						continue;
                    ++tail;
					if (tail == T)
					{
						tail = 1;
					}
                    queue[tail][0] = G.to[i];
                    queue[tail][1] = diss + 1;
                    dis[G.to[i]][diss + 1] = dis[p][diss];
					vis[G.to[i]][diss + 1] = true;
                }
            }
            else
            {
                if (dis[p][diss] + G.dis[i].num < dis[G.to[i]][diss] && diss <= m)
                {
					if (vis[G.to[i]][diss])
 						continue;
                    ++tail;
					if (tail == T)
					{
						tail = 1;
					}
                    queue[tail][0] = G.to[i];
                    queue[tail][1] = diss;
                    dis[G.to[i]][diss] = dis[p][diss] + G.dis[i].num;
					vis[G.to[i]][diss] = true;
                }
            }
        }
    }
}
void Edge::Add(int x, int y, InputData z)
{
    ++tot;
    nxt[tot] = head[x];
    to[tot] = y;
    dis[tot] = z;
    head[x] = tot;
    return;
}
InputData Read()
{
    InputData ret;
    char cha;
    cha = getchar();
    while ((cha < '0' || cha > '9') && (cha != 'x'))
    {
        cha = getchar();
    }
    if (cha == 'x')
    {
        ret.x = true;
        ret.num = 0;
        return ret;
    }
    ret.x = false;
    ret.num = 0;
    while (cha >= '0' && cha <= '9')
    {
        ret.num = ret.num * 10 + cha - '0';
        cha = getchar();
    }
    return ret;
}
bool operator<(PF &a, PF &b)
{
    return a.a == b.a ? a.b > b.b : a.a < b.a;
}
bool operator>(PF &a, PF &b)
{
    return a.a == b.a ? a.b < b.b : a.a > b.a;
}
void Qsort(int l, int r)
{
    int i = l, j = r;
    PF mid = way[(l + r) >> 1];
    while (i <= j)
    {
        while (way[i] < mid)
            ++i;
        while (way[j] > mid)
            --j;
        if (i <= j)
        {
            Swap(way[i], way[j]);
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
void Swap(PF &a, PF &b)
{
    PF temp = a;
    a = b;
    b = temp;
    return;
}
void GetAns(int a, int b)
{
    way_tot = 0;
    // memset(dis, 127 / 3, sizeof(dis));
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 0; j <= m; ++j)
		{
			dis[i][j] = INF;
		}
	}
    int inf = INF;
    BellmanFord(a);
    for (int i = 0; i <= m; ++i)
    {
        if (dis[b][i] != inf)
        {
            ++way_tot;
            way[way_tot].a = i;
            way[way_tot].b = dis[b][i];
        }
    }
    Qsort(1, way_tot);
    int last = 1;
    tmp_tot = 1;
    tmp[1] = way[1];
    if (way_tot == 0)
    {
        printf("0 0\n");
        return;
    }
    for (int i = 2; i <= way_tot; ++i)
    {
        if (way[i].b < way[last].b)
        {
            ++tmp_tot;
            tmp[tmp_tot] = way[i];
            last = i;
        }
    }
    way_tot = tmp_tot;
    for (int i = 1; i <= way_tot; ++i)
    {
        way[i] = tmp[i];
    }
    if (way[1].a != 0)
    {
        printf("inf\n");
        return;
    }
    int cnt = 1;
    long long ans = way[1].b;
    for (int i = 2; i <= way_tot; ++i)
    {
        minn[i] = ceil(1.0 * (way[1].b - way[i].b) / way[i].a) - 1;
        maxn[i] = 1;
//		printf("%d\n", minn[i]);
    }
    for (int i = 2; i <= way_tot; ++i)
    {
        for (int j = 2; j < i; ++j)
        {
            minn[i] = min(ceil(1.0 * (way[j].b - way[i].b) / (way[i].a - way[j].a)) - 1
                          , minn[i]);
        }
        for (int j = i + 1; j <= way_tot; ++j)
        {
            maxn[i] = max(ceil(1.0 * (way[j].b - way[i].b) / (way[i].a - way[j].a))
                          , maxn[i]);
        }
    }
    for (int i = 2; i <= way_tot; ++i)
    {
        if (minn[i] < maxn[i])
            continue;
        cnt += minn[i] - maxn[i] + 1;
    }
    for (int i = 2; i <= way_tot; ++i)
    {
        for (int j = maxn[i]; j <= minn[i]; ++j)
        {
            ans += j * way[i].a + way[i].b;
        }
    }
    printf("%d %lld\n", cnt, ans);
    return;
}
int min(int a, int b)
{
    return a < b ? a : b;
}
int max(int a, int b)
{
    return a > b ? a : b;
}
