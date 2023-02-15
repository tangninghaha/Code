#include <cstdio>

/* Constant */
const int MAXN = 3e5 + 5;

/* namespace */
namespace Tree
{
    struct Tree
    {
        int head[MAXN];
        int nxt[2 * MAXN];
        int to[2 * MAXN];
        int tot;
    };
    Tree G;
    int fa[MAXN];
    int dep[MAXN];
    void Init(int x);
}

/* Class */
class Segment
{
    public:
        int l;
        int r;
};
namespace Heap
{
    class Node
    {
        public:
            int l_son;
            int r_son;
    };
    class v
    {
        public:
            Node x;
            Segment key;
    };
    void DeleteMin();
    void Insert(int x);
    int FindMin();
}
/* Declaration */
int main();
void FileIO();
void Solution();
