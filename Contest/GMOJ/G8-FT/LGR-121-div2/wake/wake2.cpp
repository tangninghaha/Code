#include <cstdio>
#include <cmath>

const int MAXN = 1e7 + 5;

int main();
int gf(int x);

int twom[25];
int fa[MAXN];
int sz[MAXN];

int main()
{
    twom[0] = 1;
    for (int i = 1; i <= 24; ++i)
    {
        twom[i] = twom[i - 1] * 2;
    }
    int l, r;
    int n;
    scanf("%d%d", &l, &r);
    n = r - l + 1;
    for (int i = l; i <= r; ++i)
    {
        fa[i] = i;
        sz[i] = 1;
    }
    int wei = ceil(log2(r));
    int nxt;
    for (int i = l; i <= r; ++i)
    {
        for (int x = 0; x < wei; ++x)
        {
            nxt = i ^ twom[x];
            if (l <= nxt && nxt <= r && gf(nxt) != gf(i))
            {
                nxt = gf(nxt);
                fa[nxt] = gf(i);
                sz[gf(i)] += sz[nxt];
            }
        }
    }
    if (sz[gf(l)] == n)
    {
        printf("Yes");
    }
    else
    {
        printf("No");
    }
}
int gf(int x)
{
    if (fa[x] == x)
        return x;
    return fa[x] = gf(fa[x]);
}
