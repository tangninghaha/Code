#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 20;
int n,v[maxn],ans = -1,tot = 0,mi;
bool p[maxn],pp[maxn],pt[maxn],pd;

int max(int a,int b)
{
	return a > b ? a : b;
}

void dfs(int x,int now,int len)
{
	if (pd) return;
	if (len == x)
	{
		pd = 1;
		for (int i = 1; i <= n; i ++) pp[i] = p[i];
		return;
	}
	if (now > n) return;
	if (len + v[now] > x)
	{
		dfs(x,now + 1,len);
	} else
	{
		dfs(x,now + 1,len);
		if (!p[now])
		{
			p[now] = 1;
			dfs(x,now + 1,len + v[now]);
			if (pd) return;
			p[now] = 0;
		}
	}
	if (pd) return;
}

int main()
{
	scanf("%d",&n);
	for (int i = 1; i <= n; i ++) scanf("%d",&v[i]),tot += v[i];
	sort(v + 1,v + 1 + n);
	mi = v[1];
	for (int i = tot >> 2; i >= mi; i --)
	{
		memset(p,0,sizeof p);
		memset(pp,0,sizeof pp);
		pd = 0;
		dfs(i,1,0);
		if (!pd) continue;
		for (int j = 1; j <= n; j ++) p[j] = pp[j];
		pd = 0;
		dfs(i,1,0);
		if (!pd) continue;
		for (int j = 1; j <= n; j ++) p[j] = pp[j];
		for (int j = 1; j <= n; j ++) pt[j] = p[j];
		for (int j = (tot - 2 * i) >> 1; j >= mi; j --)
		{
			if (i * j <= ans) break;
			for (int k = 1; k <= n; k ++) p[k] = pt[k];
			pd = 0;
			dfs(j,1,0);
			for (int k = 1; k <= n; k ++) p[k] = pp[k];
			pd = 0;
			dfs(j,1,0);
			if (!pd) continue;
			ans = max(ans,i * j);
		}
	}

	if (~ans) printf("%d",ans); else printf("No Solution");
	return 0;
}
