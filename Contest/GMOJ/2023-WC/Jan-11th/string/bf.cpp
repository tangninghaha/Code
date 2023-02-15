#include <cstdio>
#include <iostream>
#include <string>

using std::string;

/* Constant */
const int MAXN = 205;
const int INF = 205;

/* Declaration */
int main();
void Dfs(string, int);
int ans = INF;
int Min(int, int);

/* Definition */
int main()
{
    string a;
    std::cin >> a;
    Dfs(a, 0);
    printf("%d", ans);
}
void Dfs(string a, int cost)
{
    bool pd = false;
    char last = 0;
    string tmp;
    for (int i = 0; i < a.size(); ++i)
    {
        if (a[i] != last && a[i] != 0 && a[i] != '*')
        {
            pd = true;
            last = a[i];
            tmp = a;
            for (int j = i; j < a.size(); ++j)
            {
                if (tmp[j] == '*')
                    continue;
                if (tmp[j] != a[i])
                    break;
                tmp[j] = '*';
            }
            Dfs(tmp, cost + 1);
        }
    }
    if (!pd)
    {
        ans = Min(ans, cost);
        return;
    }
}
int Min(int _a, int _b)
{
    return _a < _b ? _a : _b;
}
