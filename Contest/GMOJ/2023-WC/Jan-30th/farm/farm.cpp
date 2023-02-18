#include <cstdio>

/* Constant */
const int N = 3e5;

/* Class */
class Point
{
    public:
        int x;
        int y;
};
bool operator<(Point _a, Point _b)
{
    return _a.y < _b.y;
}

/* Declaration */
int main();

void Qsort(int, int);
template<typename T> void Swap(T&, T&);

/* Variable */
Point
