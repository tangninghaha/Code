#include <cstdio>
#include <string>
#include <cstring>

const long long T = 1e15;
const int MAXLEN = 1e4;

struct HighNum
{
    long long num[MAXLEN];
    int len;
    void operator=(int x);
    void Print();
    HighNum();
};
const int MAXN = 1e4 + 5;
using std::string;
char input[230];
string str[MAXN];
string ask[MAXN];

void FileIO();
int main();
int Max(int aa, int bb);
void Qsort(int l, int r);
void Swap(string &aa, string &bb);


HighNum a, b, c;
HighNum::HighNum()
{
    len = 0;
    memset(num, 0, sizeof(num));
    return;
}
void HighNum::operator=(int x)
{
    if (!x)
        return;
    len = 1;
    while (x)
    {
        num[len] = num[len] * 10 + x % 10;
        x /= 10;
    }
    return;
}
HighNum operator+(const HighNum& aa, const HighNum& bb)
{
    HighNum ret;
    ret.len = Max(aa.len, bb.len);
    int l = ret.len;
    for (int i = 1; i <= l; ++i)
    {
        ret.num[i] += aa.num[i] + bb.num[i];
        if (ret.num[i] >= T)
        {
            if (i == ret.len)
            {
                ++ret.len;
            }
            ret.num[i + 1] += ret.num[i] / T;
            ret.num[i] %= T;
        }
    }
    return ret;
}
void HighNum::Print()
{
    printf("%lld", num[len]);
    for (int i = len - 1; i >= 1; --i)
    {
        printf("%015lld", num[i]);
    }
    return;
}


void FileIO()
{
    freopen("car.in", "r", stdin);
    freopen("car.out", "w", stdout);
    return;
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", input);
        str[i] = input;
    }
    for (int i = 1; i <= m; ++i)
    {
        scanf("%s", input);
        ask[i] = input;
    }
    Qsort(1, n);
    int lbound, rbound, mid;
    int ans = 0;
    for (int i = 1; i <= m; ++i)
    {
        lbound = 1;
        rbound = n;
        while (lbound <= rbound)
        {
            mid = (lbound + rbound) >> 1;
            if (ask[i] < str[mid].substr(0, ask[i].length()))
            {
                rbound = mid - 1;
            }
            else if(ask[i] > str[mid].substr(0, ask[i].length()))
            {
                lbound = mid + 1;
            }
            else
            {
                ++ans;
                break;
            }
        }
    }
    printf("%d\n", ans);
    if (n == 1)
    {
        printf("%d", 1);
        return 0;
    }
    else if (n == 2)
    {
        printf("%d", 2);
        return 0;
    }
    a = 1;
    b = 2;
    for (int i = 3; i <= n; ++i)
    {
        c = a + b;
        a = b;
        b = c;
    }
    b.Print();
    return 0;
}
int Max(int aa, int bb)
{
    return aa > bb ? aa : bb;
}
void Qsort(int l, int r)
{
    int i = l, j = r;
    string mid = str[(l + r) >> 1];
    while (i <= j)
    {
        while (str[i] < mid)
            ++i;
        while (str[j] > mid)
            --j;
        if (i <= j)
        {
            Swap(str[i], str[j]);
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
void Swap(string &aa, string &bb)
{
    string tmp = aa;
    aa = bb;
    bb = tmp;
}
