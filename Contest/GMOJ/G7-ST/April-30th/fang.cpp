#include <stdio.h>

#define DEBUG

const int MAXM = 5010, MAXN = 2510;
int map[MAXM][MAXM];
int stx[MAXN], sty[MAXN], edx[MAXN], edy[MAXN], color[MAXM]; //Input data
int lsx[MAXN * 2], lsy[MAXN * 2]; //离散化后的xy坐标,st为1 to n, ed为 n+1 to 2n
int bhx[MAXN * 2], bhy[MAXN * 2]; //记录编号
int fbhx[MAXN * 2], fbhy[MAXN * 2]; //反记录编号
int ybhx[MAXN * 2], ybhy[MAXN * 2]; //离散化前的数值 

short maxl[MAXM][MAXM], maxr[MAXM][MAXM], up[MAXM][MAXM]; //悬线法

void swap(int &a, int &b) {
    int t = a;
    a = b;
    b = t;
}

void Qsort(int l, int r, int *a, int *b) {
    int i = l, j = r;
    int mid = a[(l + r) / 2];
    do {
        while (a[i] < mid) i++;
        while (a[j] > mid) j--;
        if (i <= j) {
            swap(a[i], a[j]);
            swap(b[i], b[j]);
            i++;
            j--;
        }
    }while (i < j);
    if (i < r) Qsort(i, r, a, b);
    if (l < j) Qsort(l, j, a, b);
}

void Lisan(int n) {
    Qsort(1, 2 * n, lsx, bhx);
    Qsort(1, 2 * n, lsy, bhy);
    
    for (int i = 1; i <= 2 * n; i++) {
        fbhx[bhx[i]] = i;
        fbhy[bhy[i]] = i;
    }
    
//    #ifdef DEBUG
//    for (int i = 1; i <= n; i++) {
//        printf("%d %d %d %d\n", lsx[fbhx[i]], lsy[fbhy[i]],
//        lsx[fbhx[i + n]], lsy[fbhy[i + n]]);
//    }
//    #endif
    
    int lastx = lsx[1], lasty = lsy[1], kx = 1, ky = 1;
    ybhx[1] = lsx[1];
    ybhy[1] = lsy[1];
    lsx[1] = 1;
    lsy[1] = 1;
    for (int i = 2; i <= 2 * n; i++) {
        if (lsx[i] == lastx) {
            lsx[i] = lsx[i - 1];
        }
        else {
            kx++;
            lastx = lsx[i];
            lsx[i] = kx;
            ybhx[kx] = lastx;
        }
        if (lsy[i] == lasty) {
            lsy[i] = lsy[i - 1];
        }
        else {
            ky++;
            lasty = lsy[i];
            lsy[i] = ky;
            ybhy[ky] = lasty;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int xx = lsx[fbhx[i]]; xx <= lsx[fbhx[i + n]] - 1; xx++) {
            for (int yy = lsy[fbhy[i]]; yy <= lsy[fbhy[i + n]] - 1; yy++) {
                map[xx][yy] = color[i];
            }
        }
//        #ifdef DEBUG
//        printf("%d %d %d %d\n", lsx[fbhx[i]], lsy[fbhy[i]],
//        lsx[fbhx[i + n]], lsy[fbhy[i + n]]);
//        #endif
    }
}
int min(int a, int b) {
    return a < b ? a : b;
}
int max(int a, int b) {
    return a > b ? a : b;
}
long long maxlong(long long a, long long b) {
    return a > b ? a : b;
}

void LineInit(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (map[i][j]) {
                up[i][j] = i;
                maxl[i][j] = j;
                maxr[i][j] = j;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (map[i][j] == map[i][j - 1] && map[i][j]) {
                maxl[i][j] = maxl[i][j - 1];
            }
            if(map[i][j] == map[i][j + 1] && map[i][j]) {
                maxr[i][j] = maxr[i][j - 1];
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (map[i][j] == map[i - 1][j] && map[i][j]) {
                up[i][j] = up[i - 1][j];
                maxl[i][j] = max(maxl[i][j], maxl[i - 1][j]);
                maxr[i][j] = min(maxr[i][j], maxr[i - 1][j]);
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d%d%d", &stx[i], &sty[i], &edx[i], &edy[i], &color[i]);
        lsx[i] = stx[i];
        lsx[i + n] = edx[i];
        lsy[i] = sty[i];
        lsy[i + n] = edy[i];
    }
    for (int i = 1; i <= 2 * n; i++) {
        bhx[i] = bhy[i] = i;
    }
    
    Lisan(n);

    LineInit(n);
    
    #ifdef DEBUG
    for (int i = 1; i <= 2 * n; i++) {
        for (int j = 1; j <= 2 * n; j++) {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d ", up[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    #endif
    
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (map[i][j]) {
                ans = maxlong(ans,
                (ybhx[fbhx[i + n]] - ybhx[up[i][j]]) * (ybhy[fbhx[bhx[maxr[i][j]] + n]] - ybhy[maxl[i][j]]));
            }
        }
    }
    printf("%lld", ans);


    return 0;
}
