#include<cstdio>
#define ma 5050
#define min(a,b) a<b?a:b
int n,m,ans=0,x,y,c;
int g[ma][ma],f[ma][ma],h[ma],vh[ma],aim[ma];

int dfs(int x,int flow)
{
	if (x==n)return flow;
    int i,k,mi=n+1;
	for (int j=1;j<=g[x][0];j++)
	{
		i=g[x][j];
		if (f[x][i]>0)
		{
			mi=h[i];
			if (h[i]+1==h[x])
			{
				k=dfs(i,min(flow,f[x][i]));
				if (k>0)
				{
					f[x][i]-=k;
					f[i][x]+=k;
					return k;
				}
				if (h[1]>n)return 0;
			}
		}
		if (++aim[x]>g[x][0]) aim[x]=1;
	}
	if (--vh[h[x]]==0) h[1]=n+1;
	h[x]=mi+1;
	vh[h[x]]++;
	return 0;
}

int main(){
	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	scanf("%d%d",&m,&n);
	for (int i=1;i<=n;i++)
	{
	    aim[i]=1;
		for (int j=1;j<=n;j++) f[i][j]=0;
	}
	for (int i=0;i<m;i++)
	{
	    scanf("%d%d%d",&x,&y,&c);
	    if ((f[x][y]==0)&&(f[y][x]==0))
		{
	       g[x][++g[x][0]]=y;
	       g[y][++g[y][0]]=x;
	    }
	    f[x][y]+=c;
	}
	while (h[1]<=n)
	      ans+=dfs(1,20000000);
    printf("%d\n",ans);
    return 0;
}
