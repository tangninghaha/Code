#include <cstdio>

/* Constant */
const int MAXK = 725;

/* Declaration */
int main();
void Init();
long long GetNum(long long);
bool Pd(int, int);
void FileIO();

/* Variable */
long long ans[MAXK];
long long all;

/* Definition */
void FileIO()
{
    freopen("time.in", "r", stdin);
    freopen("time.out", "w", stdout);
    return;
}
int main()
{
    FileIO();
    int d;
    scanf("%d", &d);
    long long t;
    Init();
    for (int dd = 1; dd <= d; ++dd)
    {
        scanf("%lld", &t);
        printf("%lld\n", GetNum(t));
    }
    return 0;
}
long long GetNum(long long _t)
{
    return (_t / 720) * all + ans[_t % 720];
}
void Init()
{
    int hour, min;
    int time = 0;
    for (min = 1; min <= 59; ++min)
    {
        ++time;
        ans[time] = ans[time - 1];
        if (Pd(12, min))
        {
            ++ans[time];
        }
    }
    for (hour = 1; hour <= 11; ++hour)
    {
        for (min = 0; min <= 59; ++min)
        {
            ++time;
            ans[time] = ans[time - 1];
            if (Pd(hour, min))
            {
                ++ans[time];
            }
        }
    }
    all = ans[time];
    return;
}
bool Pd(int _h, int _m)
{
    if (_h < 10)
    {
        if (_h - _m / 10 == _m / 10 - _m % 10)
        {
            return true;
        }
        return false;
    }
    else
    {
        if (_h / 10 - _h % 10 == _h % 10 - _m / 10
            && _h % 10 - _m / 10 == _m / 10 - _m % 10)
        {
            return true;
        }
        return false;
    }
    return false;
}
