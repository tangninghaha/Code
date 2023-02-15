#include <cstdio>
#include <cmath>
#include <ctime>

const int MAXN = 1e7 + 5;

int main();
void Dfs(int);
int Gf(int);

bool vis[MAXN];
int a[MAXN];
int ans[MAXN];
int twom[25];
int fa[MAXN];
int sz[MAXN];

int wei;
int l, r, n;
bool pd = false;

int main()
{
    twom[0] = 1;
    for (int i = 1; i <= 24; ++i)
    {
        twom[i] = twom[i - 1] * 2;
    }
    scanf("%d%d", &l, &r);
    wei = ceil(log2(r));
    n = r - l + 1;
    if (n <= 20)
    {
        for (int i = l; i <= r; ++i)
        {
            a[1] = i;
            vis[i] = true;
            Dfs(2);
            vis[i] = false;
            if (pd)
                break;
        }
        if (!pd)
        {
            printf("No");
        }
    }
    else
    {
        for (int i = l; i <= r; ++i)
        {
            fa[i] = i;
            sz[i] = 1;
        }
        int nxt;
        for (int i = l; i <= r; ++i)
        {
            for (int x = 0; x < wei; ++x)
            {
                nxt = i ^ twom[x];
                if (l <= nxt && nxt <= r && Gf(nxt) != Gf(i))
                {

                    nxt = Gf(nxt);
                    fa[nxt] = Gf(i);
                    sz[Gf(i)] += sz[nxt];
                }
            }
        }
        if (sz[Gf(l)] == n)
        {
            printf("Yes");
        }
        else
        {

            printf("No");
        }
    }
}
int Gf(int _x)
{
    if (fa[_x] == _x)
    {
        return _x;
    }
    return fa[_x] = Gf(fa[_x]);
}

void Dfs(int x)
{
    if (x > n)
    {
        pd = true;
        printf("Yes\n");
        printf("%d ", a[1]);
        for (int i = 2; i <= n; ++i)
        {
            printf("%c", (char)(ans[i] + 'a'));
        }
        return;
    }
    for (int i = 0; i < wei; ++i)
    {
        a[x] = a[x - 1] ^ twom[i];
        ans[x] = i;
        if (!vis[a[x]] && a[x] >= l && a[x] <= r)
        {
            vis[a[x]] = true;
            Dfs(x + 1);
            if (pd)
                return;
            vis[a[x]] = false;
        }
    }
    return;
}
