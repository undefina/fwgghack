#include <bits/stdc++.h>
using namespace std;
//
#define IOS ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define ios ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define qwq ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define QWQ ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define jump ;return 0;
#define space " "
using mainint=signed;using ll=long long;using ull=unsigned long long;using ld=long double;template<class T>void gmin(T &a,T b){if(a>b) a=b;}template<class T>void gmax(T &a,T b){if(a<b) a=b;}using pii=pair<int,int>;using pll=pair<ll,ll>;using pil=pair<int,ll>;using Pli=pair<ll,int>;const int INF=0x3f3f3f3f;const ll INFINF=0x3f3f3f3f3f3f3f3f;
//dist(rnd)
//
struct edge{
	int u,v,w;
}e[10005];
int id[105],in[105],pre[105],used[105];
int zhuliu(int root,int n,int m){
	int ans=0;
	while(1){
		for(int i=1;i<=n;++i) in[i]=INF;
		for(int i=1;i<=m;++i){
			int u=e[i].u,v=e[i].v;
			if(e[i].w<in[v] && u!=v){
				in[v]=e[i].w;
				pre[v]=u;
			}
		}
		for(int i=1;i<=n;++i){
			if(i==root) continue;
			if(in[i]==INF) return -1;
		}
		int cnt=0;
		memset(id,0,sizeof(id));
		memset(used,0,sizeof(used));
		in[root]=0;
		for(int i=1;i<=n;++i){
			ans+=in[i];
			int j=i;
			while(used[j]!=i && id[j]==0 && j!=root){
				used[j]=i;
				j=pre[j];
			}
			if(j!=root && id[j]==0){
				cnt++;
				for(int k=pre[j];k!=j;k=pre[k]) id[k]=cnt;
				id[j]=cnt;
			}
		}
		if(cnt==0) break;
		for(int i=1;i<=n;++i)
			if(id[i]==0) id[i]=++cnt;
		for(int i=1;i<=m;++i){
			int u=e[i].u,v=e[i].v;
			e[i].u=id[u];e[i].v=id[v];
			if(id[u]!=id[v]) e[i].w-=in[v];
		}
		n=cnt;
		root=id[root];
	}
	return ans;
}
mainint main(){
	qwq
	int n,m,root;
	cin>>n>>m>>root;
	for(int i=1;i<=m;++i){
		cin>>e[i].u>>e[i].v>>e[i].w;
		if(e[i].u==e[i].v) e[i].w=INF;
	}
	cout<<(zhuliu(root,n,m));
}
//tarjan
/*
#include <bits/stdc++.h>
using namespace std;
//
#define IOS ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define ios ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define qwq ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define QWQ ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define jump ;return 0;
#define space " "
using mainint=signed;using ll=long long;using ull=unsigned long long;using ld=long double;template<class T>void gmin(T &a,T b){if(a>b) a=b;}template<class T>void gmax(T &a,T b){if(a<b) a=b;}using pii=pair<int,int>;using pll=pair<ll,ll>;using pil=pair<int,ll>;using Pli=pair<ll,int>;const int INF=0x3f3f3f3f;const ll INFINF=0x3f3f3f3f3f3f3f3f;
//dist(rnd)
//
#define int long long
struct node{
	int l,r,w,dis,u,v,lazy;
}t[2000005];
int idx;
int bcj[2000005];
void initialize()
{
	for(int i=0;i<=2000001;++i)
		bcj[i]=i;
}
int Find(int x)
{
	return bcj[x]==x ? bcj[x] : bcj[x]=Find(bcj[x]);
}
void spread(int p){
	if(t[p].lazy){
		t[t[p].l].w+=t[p].lazy;
		t[t[p].l].lazy+=t[p].lazy;
		t[t[p].r].w+=t[p].lazy;
		t[t[p].r].lazy+=t[p].lazy;
		t[p].lazy=0;
	}
}
int merge(int p,int q){
	if(!p || !q) return p|q;
	spread(p),spread(q);
	if(t[p].w>t[q].w) swap(p,q);
	t[p].r=merge(t[p].r,q);
	if(t[t[p].l].dis<t[t[p].r].dis) swap(t[p].l,t[p].r);
	t[p].dis=t[t[p].r].dis+1;
	return p;
}
int pop(int p){
	spread(p);
	return merge(t[p].l,t[p].r);
}
int root[2000005];
int newnode(int u,int v,int w){
	t[++idx]={0,0,w,0,u,v,0};
	return idx;
}
vector<int> vec[2000005];
int sta[2000005],top,ins[2000005];
mainint main(){
	qwq
	int n,m,rt;
	cin>>n>>m>>rt;
	initialize();
	for(int i=1,u,v,w;i<=m;++i){
		cin>>u>>v>>w;
		vec[v].push_back(newnode(u,v,w));
	}
	for(int i=1;i<=n;++i){
		int to=(i==1 ? n : i-1);
		vec[i].push_back(newnode(to,i,INFINF));
	}
	for(int i=1;i<=n;++i){
		for(int k:vec[i]){
			root[i]=merge(root[i],k);
		}
	}
	sta[++top]=rt;
	ins[rt]=1;
	ll ans=0;
	int cnt=n;
	while(root[sta[top]]){
		if(ans>=INFINF) break;
		int &p=root[sta[top]];
		int u=Find(t[p].u);
		if(u==sta[top]){
			p=pop(p);continue;
		}
		if(!ins[u]){
			sta[++top]=u;
			ins[u]=1;
			continue;
		}
		int q=++cnt;
		while(ins[u]){
			int v=sta[top--];
			ins[v]=0;
			bcj[v]=q;
			node &tmp=t[root[v]];
			tmp.lazy-=tmp.w;
			if(Find(tmp.v)!=Find(rt)) ans+=tmp.w;
			root[v]=pop(root[v]);
			root[q]=merge(root[q],root[v]);
		}
		sta[++top]=q;
		ins[q]=1;
	}
	if(ans>=INFINF) cout<<-1;
	else cout<<ans;
}
*/
/*
ROUTE OUTPUT
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int maxN = 1e6 + 7;
int N, M;
struct Eddge
{
    int u, v, val, id, real;
    Eddge(int a=0, int b=0, int c=0, int d=0, int f=0):u(a), v(b), val(c), id(d), real(f) {}
}edge[maxN];
int id[maxN], vis[maxN], in[maxN], pre[maxN], las_Eddge[maxN], used[maxN] = {0}, add_E[maxN] = {0}, dele_E[maxN] = {0};
int Dir_MST(int root, int V, int E)
{
    int ans = 0, E_id = E;
    while(true)
    {
        for(int i=1; i<=V; i++) in[i] = INF;
        for(int i=1; i<=E; i++)
        {
            int u = edge[i].u, v = edge[i].v;
            if(u != v && in[v] > edge[i].val)
            {
                in[v] = edge[i].val;
                pre[v] = u;
                las_Eddge[v] = edge[i].id;
            }
        }
        for(int i=1; i<=V; i++)
        {
            if(i == root) continue;
            if(in[i] == INF) return -1;
        }
        int cnt = 0;
        memset(id, -1, sizeof(id)); memset(vis, -1, sizeof(vis));
        in[root] = 0;
        for(int i=1; i<=V; i++)
        {
            ans += in[i];
            if(i != root) used[las_Eddge[i]]++;
            int v = i;
            while(vis[v] != i && id[v] == -1 && v != root)
            {
                vis[v] = i;
                v = pre[v];
            }
            if(id[v] == -1 && v != root)
            {
                cnt++;
                for(int u=pre[v]; u!=v; u=pre[u]) id[u] = cnt;
                id[v] = cnt;
            }
        }
        if(cnt == 0) break;
        for(int i=1; i<=V; i++) if(id[i] == -1) id[i] = ++cnt;
        for(int i=1; i<=E; i++)
        {
            int u = edge[i].u, v = edge[i].v;
            edge[i].u = id[u];  edge[i].v = id[v];
            if(id[u] != id[v])
            {
                edge[i].val -= in[v];
                dele_E[++E_id] = las_Eddge[v];
                add_E[E_id] = edge[i].id;
                edge[i].id = E_id;
            }
        }
        V = cnt;
        root = id[root];
    }
    for(int i=E_id; i>E; i--)
    {
        if(used[i])
        {
            used[dele_E[i]]--;
            used[add_E[i]]++;
        }
    }
    return ans;
}
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%d%d", &N, &M);
    for(int i=1; i<=M; i++)
    {
        scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].val);
        edge[i].id = i; edge[i].real = edge[i].val;
    }
    int ans = Dir_MST(1, N, M);
    if(ans == -1 || ans == 0) { printf("%d\n", ans); return 0; }
    printf("%d\n", ans);
    bool flag = false;
    for(int i=1; i<=M; i++)
    {
        if(used[i] && edge[i].real)
        {
            if(flag) printf(" ");
            else flag = true;
            printf("%d", i);
        }
    }
    printf("\n");
}
*/