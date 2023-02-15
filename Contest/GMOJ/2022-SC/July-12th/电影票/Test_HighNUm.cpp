#include <stdio.h>
#include <cmath>
#include <cstring>
const int MAXLEN = 1e5;
struct tHighNum
{
    int num[MAXLEN];
    int len;
    void write();
    void operator=(int x);
    tHighNum();
};
tHighNum operator*(const tHighNum &a, const int &b);
int main()
{
    tHighNum a;
    a = 1;
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        a = a * 2;
    }
    a.write();
}

tHighNum::tHighNum()
{
    memset(num, 0, sizeof(num));
    len = 0;
}
void tHighNum::write()
{
    for (int i = len; i >= 1; --i)
    {
        printf("%d", num[i]);
    }
    return;
}
void tHighNum::operator=(int x)
{
    int tmp = x;
    while (tmp)
    {
        ++len;
        num[len] = tmp % 10;
        tmp /= 10;
    }
    return;
}
tHighNum operator*(const tHighNum &a, const tHighNum &b)
{
    tHighNum ret;
    ret.len = a.len + b.len;
    for (int i = 1; i <= b.len; ++i)
    {
        for (int j = 1; j <= a.len; ++j)
        {
            ret.num[i + j - 1] += b.num[i] * a.num[j];
            if (ret.num[i] >= 10)
            {
                ret.num[i + 1] += ret.num[i] / 10;
                ret.num[i] %= 10;
            }
        }
    }
    while (ret.num[ret.len] == 0)
    {
        --ret.len;
    }
    return ret;
}
tHighNum operator*(const tHighNum &a, const int &b)
{
    tHighNum ret;
    ret.len = a.len + 5;
    for (int i = 1; i <= a.len; ++i)
    {
        ret.num[i] += a.num[i] * b;
        if (ret.num[i] >= 10)
        {
            ret.num[i + 1] += ret.num[i] / 10;
            ret.num[i] %= 10;
        }
    }
    while (ret.num[ret.len] == 0)
    {
        --ret.len;
    }
    return ret;
}
