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
//无源汇上下界可行流
/*
#define int ll
struct edge{
	int u,v,cap,flow,id;
};
vector<edge> vec;
vector<int> edgeid[205];
void addedge(int u,int v,int cap,int id){
	vec.push_back({u,v,cap,0,id});
	vec.push_back({v,u,0,0,-1});
	edgeid[u].push_back(vec.size()-2);
	edgeid[v].push_back(vec.size()-1);
}
int dep[205];
int s,t;
bool bfs(){
	queue<int> que;
	memset(dep,0,sizeof(dep));
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
int lead[205];
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
int dinic(){
	int maxflow=0;
	while(bfs()){
		memset(lead,0,sizeof(lead));
		maxflow+=dfs(s,INFINF);
	}
	return maxflow;
}
int indeg[205],outdeg[205],a[10205],minflow[10205];
mainint main(){
	qwq
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;++i){
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		addedge(a,b,d-c,i);
		outdeg[a]+=c;
		indeg[b]+=c;
		minflow[i]=c;
	}
	s=n+1,t=n+2;
	for(int i=1;i<=n;++i)
		if(indeg[i]-outdeg[i]>=0) addedge(s,i,indeg[i]-outdeg[i],-1);
		else addedge(i,t,-(indeg[i]-outdeg[i]),-1);
	dinic();
	for(int i:edgeid[s]){
		edge e=vec[i];
		if(e.cap>e.flow){
			cout<<"NO";return 0;//不存在可行流
		}
	}
	cout<<"YES"<<'\n';
	for(edge e:vec){
		if(e.id>0) a[e.id]=e.flow;
	}
	for(int i=1;i<=m;++i) cout<<a[i]+minflow[i]<<'\n';//每条边的实际流量
}
*/



//有源汇上下界可行流：
//t->s连一个下界为0，上界INF的边，同无源汇可行流一样处理即可。







//有源汇上下界最大流
/*
#define int ll
struct edge {
    int u, v, cap, flow, id;
};
vector<edge> vec;
vector<int> edgeid[205];
void addedge(int u, int v, int cap, int id) {
    vec.push_back({u, v, cap, 0, id});
    vec.push_back({v, u, 0, 0, -1});
    edgeid[u].push_back(vec.size() - 2);
    edgeid[v].push_back(vec.size() - 1);
}
int dep[205];
int s, t;
bool bfs() {
    queue<int> que;
    memset(dep, 0, sizeof(dep));
    dep[s] = 1;
    que.push(s);

    while (!que.empty()) {
        int u = que.front();
        que.pop();

        for (int i : edgeid[u]) {
            edge e = vec[i];
            int v = e.v;

            if (!dep[v] && e.cap - e.flow > 0) {
                dep[v] = dep[u] + 1;
                que.push(v);
            }
        }
    }

    return dep[t];
}
int lead[205];
int dfs(int u, int flow) {
    if (u == t || flow == 0)
        return flow;

    int used = 0;

    for (int &i = lead[u]; i < edgeid[u].size(); ++i) {
        edge &e = vec[edgeid[u][i]];
        int v = e.v;
        int d;

        if (dep[v] == dep[u] + 1 && (d = dfs(v, min(flow - used, e.cap - e.flow)))) {
            used += d;
            e.flow += d;
            vec[edgeid[u][i] ^ 1].flow -= d;

            if (used == flow)
                return used;
        }
    }

    return used;
}
int dinic() {
    int maxflow = 0;

    while (bfs()) {
        memset(lead, 0, sizeof(lead));
        maxflow += dfs(s, INFINF);
    }

    return maxflow;
}
int indeg[205], outdeg[205], a[10205], minflow[10205];
mainint main() {
    qwq
    int n, m, ss, tt;
    cin >> n >> m >> ss >> tt;

    for (int i = 1; i <= m; ++i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        addedge(a, b, d - c, i);
        outdeg[a] += c;
        indeg[b] += c;
        minflow[i] = c;

    }

    s = n + 1, t = n + 2;

    for (int i = 1; i <= n; ++i)
        if (indeg[i] - outdeg[i] >= 0)
            addedge(s, i, indeg[i] - outdeg[i], -1);
        else
            addedge(i, t, -(indeg[i] - outdeg[i]), -1);

    addedge(tt, ss, INF, -1);
    dinic();

    for (int i : edgeid[s]) {
        edge e = vec[i];

        if (e.cap > e.flow) {
            cout << "please go home to sleep";
            return 0;
        }
    }

    vec.pop_back();
    int ans = vec.back().flow;
    vec.pop_back();
    edgeid[ss].pop_back();
    edgeid[tt].pop_back();
    s = ss, t = tt;
    ans += dinic();
    cout << ans;
}
*/









//有源汇上下界最小流
/*
#define int ll
struct edge {
    int u, v, cap, flow;
};
vector<edge> vec;
vector<int> edgeid[50010];
void addedge(int u, int v, int cap) {
    vec.push_back({u, v, cap, 0});
    vec.push_back({v, u, 0, 0});
    edgeid[u].push_back(vec.size() - 2);
    edgeid[v].push_back(vec.size() - 1);
}
int dep[50010];
int s, t;
bool bfs() {
    queue<int> que;
    memset(dep, 0, sizeof(dep));
    dep[s] = 1;
    que.push(s);

    while (!que.empty()) {
        int u = que.front();
        que.pop();

        for (int i : edgeid[u]) {
            edge e = vec[i];
            int v = e.v;

            if (!dep[v] && e.cap - e.flow > 0) {
                dep[v] = dep[u] + 1;
                que.push(v);
            }
        }
    }

    return dep[t];
}
int lead[50010];
int dfs(int u, int flow) {
    if (u == t || flow == 0)
        return flow;

    int used = 0;

    for (int &i = lead[u]; i < edgeid[u].size(); ++i) {
        edge &e = vec[edgeid[u][i]];
        int v = e.v;
        int d;

        if (dep[v] == dep[u] + 1 && (d = dfs(v, min(flow - used, e.cap - e.flow)))) {
            used += d;
            e.flow += d;
            vec[edgeid[u][i] ^ 1].flow -= d;

            if (used == flow)
                return used;
        }
    }

    return used;
}
int dinic() {
    int maxflow = 0;

    while (bfs()) {
        memset(lead, 0, sizeof(lead));
        maxflow += dfs(s, INFINF);
    }

    return maxflow;
}
int indeg[50010], outdeg[50010], minflow[125010];
mainint main() {
    qwq
    int n, m, ss, tt;
    cin >> n >> m >> ss >> tt;

    for (int i = 1; i <= m; ++i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        addedge(a, b, d - c);
        outdeg[a] += c;
        indeg[b] += c;
        minflow[i] = c;

    }

    s = n + 1, t = n + 2;

    for (int i = 1; i <= n; ++i)
        if (indeg[i] - outdeg[i] >= 0)
            addedge(s, i, indeg[i] - outdeg[i]);
        else
            addedge(i, t, -(indeg[i] - outdeg[i]));

    addedge(tt, ss, INFINF);
    dinic();

    for (int i : edgeid[s]) {
        edge e = vec[i];

        if (e.cap > e.flow) {
            cout << "please go home to sleep";
            return 0;
        }
    }

    vec.pop_back();
    int ans = vec.back().flow;
    vec.pop_back();
    edgeid[ss].pop_back();
    edgeid[tt].pop_back();
    s = tt, t = ss;
    ans -= dinic();
    cout << ans;
}
*/




/*
无源汇上下界最小费用可行流

同样建立超级源汇S,T

对于边(u,v,L,R,cost)，建边(u,v,R−L,cost)，并将初始值加上L*cost

对于那些流量不平衡的点，建边同 “ 无源汇上下界可行流 ”，费用为 0

然后跑 S 到 T 的最小费用最大流

有源汇加一条原图中(T,S,∞,0)
*/



/*
上下界最小费用可行流。（就是满足所有边的流量上下限制，同时费用最小）
按照如下方式建立附加边和附加点：

1.建立附加源点SS，和附加汇点TT

2.对于原图中每一个点（包括源汇）u,令d[u]代表u点的所有入边的流量下界减去出边的流量下界

2.1.如果d[u]是负数，那么从u连一条边(u,TT,0,-d[u])到TT

2.2.如果d[u]是正数，那么从SS连一条边(SS,u,0,d[u])到u

3.对于原图中每一条边(u,v,w,l,r)，连边(u,v,w,r-l)

4.连边(t,s,0,inf)（注意这里是原图的源汇点！不是附加的源汇点！！）

这样以后，从SS到TT跑新图的最小费用最大流，再加上原图中每条边的下界流量乘以费用（必须跑的部分），就是最小费用可行流的费用了

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

#define int ll
struct edge{
	int u,v,cap,flow,cost;
};
vector<edge> vec;
vector<int> edgeid[305];
void addedge(int u,int v,int cap,int cost){
	vec.push_back({u,v,cap,0,cost});
	vec.push_back({v,u,0,0,-cost});
	edgeid[u].push_back(vec.size()-2);
	edgeid[v].push_back(vec.size()-1);
}
int num,s,t;
struct qpair{
	int first,second;
};
bool operator <(qpair a,qpair b){
		if(a.first==b.first) return a.second>b.second;
		return a.first>b.first;
	}
int d[305];
bool used[305];
void initdijk(){
	memset(d,0x3f,sizeof(d));
	memset(used,0,sizeof(used));
	priority_queue<qpair> que;
	que.push({0,s});
	d[s]=0;
	while(!que.empty()){
		qpair p=que.top();
		que.pop();
		int u=p.second;
		if(used[u]) continue;
		used[u]=1;
		for(int i:edgeid[u]){
			edge e=vec[i];
			int v=e.v;
			if(e.flow!=e.cap && d[v]>d[u]+e.cost){
				d[v]=d[u]+e.cost;
				que.push({d[v],v});
			}
		}
	}
}
int dis[305],pre[305];
bool dijkstra(){
	priority_queue<qpair> que;
	memset(dis,0x3f,sizeof(dis));
	memset(used,0,sizeof(used));
	que.push({0,s});
	dis[s]=0;
	while(!que.empty()){
		qpair p=que.top();
		que.pop();
		int u=p.second;
		if(used[u]) continue;
		used[u]=1;
		for(int i:edgeid[u]){
			edge e=vec[i];
			int v=e.v,c=e.cost+d[u]-d[v];
			if(e.flow!=e.cap && dis[v]>dis[u]+c){
				dis[v]=dis[u]+c;
				pre[v]=i;
				que.push({dis[v],v});
			}
		}
	}
	return dis[t]!=INFINF;
}
int maxf=0,minc=0;
void primal(){
	initdijk();
	maxf=0,minc=0;
	while(dijkstra()){
		int minf=INFINF;
		for(int i=1;i<=num;++i) d[i]+=dis[i];
		for(int i=t;i!=s;i=vec[pre[i]].u) gmin(minf,vec[pre[i]].cap-vec[pre[i]].flow);
		for(int i=t;i!=s;i=vec[pre[i]].u){
			vec[pre[i]].flow+=minf;
			vec[pre[i]^1].flow-=minf;
		}
		maxf+=minf;
		minc+=minf*d[t];
	}
}
int n,k,indeg[305],outdeg[305];
mainint main(){
	qwq
	cin>>n;
	int ss=n+1,tt=n+2;
	s=tt+1,t=s+1;
	addedge(s,1,INF,0);
	int sum=0;
	for(int i=1,m,v,p;i<=n;++i){
		cin>>m;
		while(m--){
			cin>>v>>p;
			addedge(i,v,INF,p);
			indeg[v]++,outdeg[i]++;//这里是1因为边的流量下界是1.
			sum+=p;//p是一条边的费用，注意应该还要乘流量下界！
		}
	}
	for(int i=1;i<=n;++i){
		addedge(i,tt,INF,0);
	}
	for(int i=1;i<=tt;++i){
		if(indeg[i]>outdeg[i]) addedge(s,i,indeg[i]-outdeg[i],0);
		else addedge(i,t,-(indeg[i]-outdeg[i]),0);
	}
	addedge(tt,ss,INF,0);
	num=t;
	primal();
	cout<<minc+sum;
}
*/