#include <bits/stdc++.h>
using namespace std;
//
#define IOS ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define ios ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define qwq ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define QWQ ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define jump ;return 0;
#define space " "
#define line '\n'
using mainint=signed;using ll=long long;using ull=unsigned long long;using ld=long double;template<class T>void gmin(T &a,T b){if(a>b) a=b;}template<class T>void gmax(T &a,T b){if(a<b) a=b;}using pii=pair<int,int>;using pll=pair<ll,ll>;using pil=pair<int,ll>;using Pli=pair<ll,int>;const int INF=0x3f3f3f3f;const ll INFINF=0x3f3f3f3f3f3f3f3f;
//dist(rnd)
//

vector<int> vec[500005];
int dep[500005],top[500005],son[500005],siz[500005],fa[500005],dfn[500005],dfnidx,num[500005];
void dfs1(int u,int f)
{
	siz[u]=1;
	for(int v:vec[u]){
		if(v==f) continue;
		fa[v]=u;
		dep[v]=dep[u]+1;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]]) son[u]=v;
	}
}
void dfs2(int u,int tp)
{
	dfn[u]=++dfnidx;
	num[dfnidx]=u;
	top[u]=tp;
	if(!son[u]) return;
	dfs2(son[u],tp);
	for(int v:vec[u]){
		if(v!=fa[u] && v!=son[u]) dfs2(v,v);
	}
} 
int lca(int x,int y)
{
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	return x;
}
int getdis(int x,int y){
	return dep[x]+dep[y]-2*dep[lca(x,y)];
}
int upjump(int x,int d){
	while(dep[top[x]]>d) x=fa[top[x]];
	return num[dfn[top[x]]-dep[top[x]]+d];
}
int jumpk(int s,int t,int k){
	int LCA=lca(s,t),len=getdis(s,t)+1;
	if(k<=dep[s]-dep[LCA]+1) return upjump(s,dep[s]-k+1);
	else return upjump(t,dep[t]-len+k);
}
/*
struct node
{
	int l,r;
	ll lazy,sum;
}t[400005];
#define mod 54
void update(int p)
{
	t[p].sum=(t[p*2].sum+t[p*2+1].sum)%mod;
}
void spread(int p)
{
	if(t[p].lazy){
		t[p*2].sum+=(t[p*2].r-t[p*2].l+1)*t[p].lazy;
		t[p*2].lazy+=t[p].lazy;
		t[p*2].sum%=mod;
		t[p*2].lazy%=mod;
		t[p*2+1].sum+=(t[p*2+1].r-t[p*2+1].l+1)*t[p].lazy;
		t[p*2+1].lazy+=t[p].lazy;
		t[p*2+1].sum%=mod;
		t[p*2+1].lazy%=mod;
		t[p].lazy=0;
	}
}
void build(int p,int l,int r)
{
	t[p].l=l;t[p].r=r;
	if(l==r){
		t[p].sum=num[l];
		return;
	}
	int mid=(l+r)/2;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	update(p);
}
void change(int p,int l,int r,int v)
{
	if(l<=t[p].l && r>=t[p].r){
		t[p].sum+=(t[p].r-t[p].l+1)*v;
		t[p].lazy+=v;
		return;
	}
	spread(p);
	int mid=(t[p].l+t[p].r)/2;
	if(l<=mid) change(p*2,l,r,v);
	if(r>mid) change(p*2+1,l,r,v);
	update(p);
}
ll query(int p,int l,int r)
{
	if(l<=t[p].l && r>=t[p].r) return t[p].sum;
	spread(p);
	ll val=0;
	int mid=(t[p].l+t[p].r)/2;
	if(l<=mid) val=(val+query(p*2,l,r))%mod;
	if(r>mid) val=(val+query(p*2+1,l,r))%mod;
	return val;
}
void tchange(int x,int y,int v)
{
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		change(1,dfn[top[x]],dfn[x],v);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	change(1,dfn[x],dfn[y],v);
}
ll tquery(int x,int y)
{
	ll val=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		val=(val+query(1,dfn[top[x]],dfn[x]))%mod;
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	val=(val+query(1,dfn[x],dfn[y]))%mod;
	return val;
}
*/
int main()
{
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int n,r,m,x,y,a,b;
	cin>>n>>m>>r;
	for(int i=1;i<n;++i){
		cin>>x>>y;
		vec[x].push_back(y);
		vec[y].push_back(x);
	}
	dfs1(r,0);
	dfs2(r,r);
	for(int i=1;i<=m;++i){
		cin>>a>>b;
		cout<<lca(a,b)<<'\n';
	}
}
/*
虚树dp
int sta[1000005],tp;
void ins(int u){
	if(tp==1){
		sta[++tp]=u;
		return;
	}
	int LCA=lca(sta[tp],u);
	if(LCA==sta[tp]){
		sta[++tp]=u;return;
	}
	while(tp>1 && dfn[sta[tp-1]]>=dfn[LCA]){
		newvec[sta[tp-1]].push_back({sta[tp],dep[sta[tp]]-dep[sta[tp-1]]});
		tp--;
	}
	if(LCA!=sta[tp]){
		newvec[LCA].push_back({sta[tp],dep[sta[tp]]-dep[LCA]});
		sta[tp]=LCA;
	}
	sta[++tp]=u;
}
while(q--){
		cin>>k;
		for(int i=1;i<=k;++i) cin>>p[i],isreal[p[i]]=1;
		sort(p+1,p+1+k,cmp);
		tp=0;
		sta[++tp]=1;
		for(int i=1;i<=k;++i) if(p[i]!=1) ins(p[i]);
		while(tp>1) newvec[sta[tp-1]].push_back({sta[tp],dep[sta[tp]]-dep[sta[tp-1]]}),tp--;
		ans=0;mnl=INF;mxl=-1;
		dp(1);
		cout<<ans<<space<<mnl<<space<<mxl<<'\n';
		for(int i=1;i<=k;++i) isreal[p[i]]=0;
	}
	//在dp过程中清空newvec
*/