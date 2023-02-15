#include <cstdio>

/* Constant */
const int MAXN = 1e5 + 5;

/* Definition */
namespace LineTree
{
    long long tree[MAXN * 4];
    long long lazy_tag[MAXN * 4];
    void Update(int, int, int, int, int, int);
    void Build(int, int, int);
    long long GetSum(int, int, int, int, int);
    void DownLazyTag(int);
};
namespace Tree
{
    struct Tree
    {
        int head[MAXN];
        int to[MAXN * 2];
        int nxt[MAXN * 2];
        int tot;
        void Add(int, int);
    };
    Tree T;
    
    int fa[MAXN];
    int size[MAXN];
    int dep[MAXN];

    int heavy_son[MAXN];
    int top[MAXN];
    int dfn[MAXN];

    void Init(int x);
    void Dfs(int x, int top);
}
int main();
void Sovle();

/* Variable */
int fs[MAXN];
int person[MAXN];

/* Definition */
int main()
{
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &fs[i]);
    }
    LineTree::Build(1, 1, 1);
    for (int i = 1; i < n; ++i)
    {
        scanf("%d%d", &_u, &_v);
        Tree::T.Add(_u, _v);
        Tree::T.Add(_v, _u);
    }
    Tree::Init(1);
    Tree::Dfs(1, 1);
    for (int i = 1; i <= q; ++i)
    {
        while (cha != 'Q' && cha != 'C')
        {
            cha = getchar();
        }
        if (cha == 'Q')
        {
            int x;
            int k = 0;
            while (scanf("%d", &x))
            {
                ++k;
                person[k] = x;
            }
            Sovle(k);
        }
        else
        {
            int x, w;
            scanf("%d%d", &x, &w);
            LineTree::Update(1, n, x, x, 1, w);
        }
    }
    return 0;
}
void LineTree::Build(int l, int r, int k)

