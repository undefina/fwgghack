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
#define m0(a) memset((a),0,sizeof(a));
#define mINF(a) memset((a),0x3f,sizeof(a));
#define mNINF(a) memset((a),-0x3f,sizeof(a));
#define mNeg(a) memset((a),-1,sizeof(a));
using mainint = signed;using ll = long long;using ull = unsigned long long;using ld = long double;template<class T>void gmin(T &a,T b){if(a>b) a=b;}template<class T>void gmax(T &a,T b){if(a<b) a=b;}using pii=pair<int,int>;using pll=pair<ll,ll>;using pil=pair<int,ll>;using Pli=pair<ll,int>;const int INF=0x3f3f3f3f;const ll INFINF=0x3f3f3f3f3f3f3f3f;
mt19937_64 rnd(time(0)); 
uniform_int_distribution<long long> dist(12,8000000000);
//dist(rnd)
#define int ll
struct dinicqwq{
    struct edge{
        int u,v,cap,flow;
    };
    vector<edge> vec;
    vector<int> edgeid[505];
    void addedge(int u,int v,int cap){
        vec.push_back({u,v,cap,0});
        vec.push_back({v,u,0,0});
        edgeid[u].push_back(vec.size()-2);
        edgeid[v].push_back(vec.size()-1);
    }
    int dep[505];
    int s,t;
    void clear(){
        for(auto &e:vec) e.flow=0;
    }
    bool bfs(){
        queue<int> que;
        memset(dep,0,sizeof(dep));
        m0(lead);
        dep[s]=1;
        que.push(s);
        while(!que.empty()){
            int u=que.front();
            que.pop();
            for(int i:edgeid[u]){
                edge e=vec[i];
                int v=e.v;
                if(!dep[v] && e.cap-e.flow>0){
                    dep[v]=dep[u]+1;
                    que.push(v);
                }
            }
        }
        return dep[t];
    }
    int lead[505];
    int dfs(int u,int flow){
        if(u==t || flow==0) return flow;
        int used=0;
        for(int &i=lead[u];i<edgeid[u].size();++i){
            edge &e=vec[edgeid[u][i]];
            int v=e.v;
            int d;
            if(dep[v]==dep[u]+1 && (d=dfs(v,min(flow-used,e.cap-e.flow)))){
                used+=d;
                e.flow+=d;
                vec[edgeid[u][i]^1].flow-=d;
                if(used==flow) return used;
            }
        }
        return used;
    }
    int Dinic(){
        int maxflow=0;
        clear();
        while(bfs()){
            memset(lead,0,sizeof(lead));
            maxflow+=dfs(s,INFINF);
        }
        return maxflow;
    }
}dinic;
vector<pll> vec[505];
int id[505],col[505],temp[505];
void dfs(int u,int c){
    col[u]=c;
    for(int i:dinic.edgeid[u]){
        auto e=dinic.vec[i];
        int v=e.v;
        if(e.cap>e.flow && col[v]!=c) dfs(v,c);
    }
}
int colidx,ans;
void build(int l,int r){
    if(l==r) return;
    int u=id[l],v=id[l+1];
    dinic.s=u,dinic.t=v;
    int sum=dinic.Dinic();
    vec[u].push_back({v,sum});
    vec[v].push_back({u,sum});
    ans+=sum;
    dfs(u,++colidx);
    int L=l,R=r;
    for(int i=l;i<=r;++i){
        if(col[id[i]]==colidx) temp[L++]=id[i];
        else temp[R--]=id[i];
    }
    for(int i=l;i<=r;++i) id[i]=temp[i];
    build(l,L-1);build(R+1,r);
}
int dep[505],top[505],son[505],siz[505],fa[505],val[505];
void dfs1(int u,int f)
{
	siz[u]=1;
	for(auto vv:vec[u]){
        int v=vv.first;
		if(v==f) continue;
		fa[v]=u;
        val[v]=vv.second;
		dep[v]=dep[u]+1;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]]) son[u]=v;
	}
}
void dfs2(int u,int tp)
{
	top[u]=tp;
	if(!son[u]) return;
	dfs2(son[u],tp);
	for(auto vv:vec[u]){
        int v=vv.first;
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
int query(int u,int v){
    int LCA=lca(u,v);
    int ans=INF;
    for(int i=u;i!=LCA;i=fa[i]) gmin(ans,val[i]);
    for(int i=v;i!=LCA;i=fa[i]) gmin(ans,val[i]);
    return ans;
}
bool used[505];
void solve(){
    priority_queue<pii> que;
    que.push({0,1});
    while(!que.empty()){
        auto temp=que.top();
        que.pop();
        int u=temp.second;
        used[u]=1;
        cout<<u<<space;
        for(pll vv:vec[u]){
            int v=vv.first;
            if(!used[v]) que.push({vv.second,v});
        }
    }
}
mainint main(){
	qwq
    int n,m;
    cin>>n>>m;
    for(int i=1,u,v,w;i<=m;++i){
        cin>>u>>v>>w;
        dinic.addedge(u,v,w);
        dinic.addedge(v,u,w);
    }
    for(int i=1;i<=n;++i) id[i]=i;
    build(1,n);
    dfs1(1,0);
    dfs2(1,1);
    cout<<ans<<'\n';
    solve();
}