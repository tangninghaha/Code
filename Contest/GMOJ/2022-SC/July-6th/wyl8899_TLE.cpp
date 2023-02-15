#include <stdio.h>
#include <cstring>

const int MAXN = 50005;

int max(int a, int b);

struct KMP
{
    char txt[MAXN];
    char pat[MAXN];
    int lentxt;
    int lenpat;
    int nxt[MAXN];
    void InitNxt();
    int GetLen();
};


KMP K;

int main()
{
//    freopen("data4.in", "r", stdin);
    scanf("%s", K.pat + 1);
    scanf("%s", K.txt + 1);
    K.pat[0] = K.txt[0] = '0';
    K.lenpat = strlen(K.pat) - 1;
    K.lentxt = strlen(K.txt) - 1;
    int ans = 0;
    char tmp;
    for (int i = 1; i <= K.lenpat; i++)
    {
        tmp = K.pat[i];
        K.pat[i] = '*';
        K.InitNxt();
        ans = max(ans, K.GetLen());
        K.pat[i] = tmp;
    }
    printf("%d", ans);
    return 0;
}

void KMP::InitNxt()
{
    nxt[1] = 0;
    int now_nxt = 0;
    for (int i = 2; i <= lenpat; ++i)
    {
        while(pat[i] != pat[now_nxt + 1] && pat[i] != '*' && pat[now_nxt + 1] != '*'
              && now_nxt)
        {
            now_nxt = nxt[now_nxt - 1];
        }
        if (pat[i] == pat[now_nxt + 1] || pat[i] == '*' || pat[now_nxt + 1] == '*')
        {
            ++now_nxt;
        }
        nxt[i] = now_nxt;
    }
    return;
}
int KMP::GetLen()
{
    int i = 1, j = 0;
    int ret = 0;
    while (i <= lentxt)
    {
        if (pat[j + 1] == txt[i] || pat[j + 1] == '*')
        {
            ++j;
            ++i;
            if (j > ret)
            {
                ret = j;
            }
        }
        else if (j)
        {
            j = nxt[j];
        }
        else
        {
            ++i;
        }
    }
    return ret;
}

int max(int a, int b)
{
    return a > b ? a : b;
}
