#include <stdio.h>
#define DEBUG

const long long INF = 1e15;
const int MAXNUM = 100005;

#ifdef DEBUG
int pre[MAXNUM];
int pre_type[MAXNUM];
#endif


void Dfs(int xx);
void FileIO();
int GetLen(int xx);
void GetNum();
int Hb(int *a, int l);
int main();
int Max(int a, int b);
long long Min(long long a, long long b);
long long Sovle();
void Split(int x);
void Swap(int &a, int &b);


int n;
int x[11];
bool pd[MAXNUM];
bool vis[MAXNUM];
long long ans[MAXNUM];
int tot_num;
int num[6];
int len;

void Dfs(int xx)
{
//    if (pd[xx])
//        return;
    vis[xx] = true;
//    printf("%d\n", xx);
    pd[xx] = true;
    int l = GetLen(xx), nxt;
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
#ifdef DEBUG
                if ((((x[i] & x[j]) + (x[i] ^ x[j])) * 2) < ans[nxt] && !vis[nxt])
                {
                    pre_type[nxt] = 1;
                    pre[nxt] = xx;
                }
#endif
                if (!vis[nxt])
                    ans[nxt] = Min(ans[nxt], (long long)(((x[i] & x[j]) + (x[i] ^ x[j])) * 2));
                if (!vis[nxt])
                {
                    Dfs(nxt);
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
#ifdef DEBUG
                if ((x[2] + (x[2] & x[2]) + (x[2] ^ x[2])) < ans[nxt] && !vis[nxt])
                {
                    pre_type[nxt] = 2;
                    pre[nxt] = xx;
                }
#endif
            if (!vis[nxt])
                ans[nxt] = Min(ans[nxt], (long long)(x[2] + (x[2] & x[2]) + (x[2] ^ x[2])));
            if (!vis[nxt])
            {
                Dfs(nxt);
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
#ifdef DEBUG
                if ((aa + (bb & cc) + (bb ^ cc)) < ans[nxt] && !vis[nxt])
                {
                    pre_type[nxt] = 2;
                    pre[nxt] = xx;
                }
#endif
            if (!vis[nxt])
                ans[nxt] = Min(ans[nxt], (long long)(aa + (bb & cc) + (bb ^ cc)));
            if (!vis[nxt])
            {
                Dfs(nxt);
            }
        }
    }
    if (l == len)
    {
        vis[xx] = false;
        return;
    }
//    if (l == 2)
//    {
//        Split(xx);
//        if (x[1] == x[2])
//        {
//            x[1] = -1;
//            nxt = Hb(x, l);
//            Split(xx);
//#ifdef DEBUG
//                if ((aa + (bb & cc) + (bb ^ cc)) < ans[nxt])
//                {
//                    pre_type[nxt] = 3;
//                    pre[nxt] = xx;
//                }
//#endif
//            if (!vis[nxt])
//                ans[nxt] = Min(ans[nxt], (long long)(x[2] + (x[2] & x[2]) + (x[2] ^ x[2])));
//            if (!pd[nxt] && !vis[nxt])
//            {
//                Dfs(nxt);
//            }
//        }
//    }
    for (int i = 1; i <= l + 1; ++i)
    {
        if (i > len)
            break;
//        if (l == 2)
//            break;
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
#ifdef DEBUG
                if ((aa + (bb & cc) + (bb ^ cc)) < ans[nxt] && !vis[nxt])
                {
                    pre_type[nxt] = 3;
                    pre[nxt] = xx;
                }
#endif
                if (!vis[nxt])
                    ans[nxt] = Min(ans[nxt], (long long)(aa + (bb & cc) + (bb ^ cc)));
                if (!vis[nxt])
                {
                    Dfs(nxt);
                }
            }
        }
    }
    vis[xx] = false;
}
void FileIO()
{
    freopen("problem.in", "r", stdin);
//    freopen("problem.out", "w", stdout);
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
void GetNum()
{
    for (int i = 1; i <= n; ++i)
    {
        Dfs(num[i]);
    }
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
int Max(int a,int b)
{
    return a > b ? a : b;
}
long long Min(long long a, long long b)
{
    return a < b ? a : b;
}
long long Sovle()
{
    for (int i = 1; i <= n; ++i)
    {
        len = Max(len, GetLen(num[i]));
    }
    for (int numb = 1; numb <= 99999; ++numb)
    {
        ans[numb] = INF;
    }
    GetNum();
    long long ret = 0;
    for (int i = 1; i <= n; ++i)
    {
        pd[num[i]] = false;
        ans[num[i]] = 0;
    }
    for (int numb = 1; numb <= 99999; ++numb)
    {
        if (pd[numb])
        {
            ret += ans[numb];
#ifdef DEBUG
            if (pre[pre[numb]] == numb)
            {
                printf("!!!!!!!!!!!!!!!");
            }
            printf("%d: %lld %d -> %d\n", pre_type[numb], ans[numb], pre[numb], numb);
#endif
        }
    }
    return ret;
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
void Swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
    return;
}
