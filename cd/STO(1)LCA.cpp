#include <bits/stdc++.h>
using namespace std;
const int inf=5e5+7;
int n,m,s;
int fir[inf],nex[inf<<1],poi[inf<<1],cnt;
void ins(int x,int y)
{
	nex[++cnt]=fir[x];
	poi[cnt]=y;
	fir[x]=cnt;
}
int dep[inf],sta[inf],olas;
struct Euler_Tour{
	int ola,minn;
}lca[inf<<1][21];
Euler_Tour min(Euler_Tour a,Euler_Tour b)
{
	return (a.minn>b.minn)?b:a;
}
void dfs(int now,int from)
{
	sta[now]=++olas;
	lca[olas][0].ola=now;
	dep[now]=dep[from]+1;
	lca[olas][0].minn=dep[now];
	for(int i=fir[now];i;i=nex[i])
	{
		int p=poi[i];
		if(p==from)continue;
		dfs(p,now);
		lca[++olas][0].ola=now;
		lca[olas][0].minn=dep[now];
	}
}
int main()
{
	cin>>n>>m>>s;
	for(int i=1;i<n;i++)
	{
		int u,v;
        cin>>u>>v;
		ins(u,v),ins(v,u);
	}
	dfs(s,s);
	for(int j=1;j<=21;j++)
		for(int i=1;i+(1<<(j-1))<=olas;i++)
			lca[i][j]=min(lca[i][j-1],lca[i+(1<<(j-1))][j-1]);
	for(int i=1;i<=m;i++)
	{
        int l,r;
        cin>>l>>r;
		l=sta[l],r=sta[r];
		if(l>r)swap(l,r);int len=log2(r-l+1);
		cout<<(min(lca[l][len],lca[r-(1<<len)+1][len]).ola,'\n');
	}
	return 0;
}
/*
int dpma[200005][20], dpmi[200005][20], n, m, a[200005];
void RMQ(){
    for(int i = 1; i <= n; i++){
        dpmi[i][0] = a[i], dpma[i][0] = a[i];
    }
    for(int j = 1; (1 << j) <= n; j++){
        for(int i = 1; i + (1 << j) - 1 <= n; i++){
            dpma[i][j] = max(dpma[i][j - 1], dpma[i + (1 << (j - 1))][j - 1]);
            dpmi[i][j] = min(dpmi[i][j - 1], dpmi[i + (1 << (j - 1))][j - 1]);
        }
    }
}
int QueryMax(int l, int r){
    int k = log2(r - l + 1);
    return max(dpma[l][k], dpma[r - (1 << k) + 1][k]);
}
int QueryMin(int l, int r){
    int k = log2(r - l + 1);
    return min(dpmi[l][k], dpmi[r - (1 << k) + 1][k]);
}
*/