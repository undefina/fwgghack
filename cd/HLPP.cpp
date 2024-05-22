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

//TEST THE SPEED OF THE ALGORITHM

struct HLPP {
    typedef long long Qint;
    struct Edge {
        int to;
        Qint c;
        int rev;
        Edge(int to, Qint c, int rev): to(to), c(c), rev(rev) {}
    };
    
    int n, m, s, t;
    int maxh, maxgaph, workcnt;
    vector<vector<Edge>> vec;
    vector<Qint> ov;
    vector<int> h;
    vector<int> cur;
    vector<int> ovList, ovNxt;
    vector<int> gap, gapPrv, gapNxt;
    HLPP(int n, int m, int s, int t): n(n), m(m), s(s), t(t), maxh(0), maxgaph(0), workcnt(0),
                                      vec(n+1), ov(n+1), h(n+1), cur(n+1),
                                      ovList((n+1), -1), ovNxt(n+1, -1),
                                      gap((n+1), -1), gapPrv(n+1, -1), gapNxt(n+1, -1) {}

    void addedge(int u, int v, Qint c) {
        vec[u].push_back(Edge(v, c, vec[v].size()));
        vec[v].push_back(Edge(u, 0, vec[u].size()-1));
    }
    Qint maxflow() {
        globalRelabel();
        for(auto &e: vec[s]) if(e.c) { pushFlow(s, e, e.c);  maxh = max(maxh, h[e.to]); }
        for(; maxh >= 0; --maxh) {
            while(~ovList[maxh]) {
                int x = ovList[maxh];
                ovList[maxh] = ovNxt[x];
                discharge(x);
                if(workcnt > (n<<2))  globalRelabel();
            }
        }
        return ov[t];
    }
private:
    void discharge(int x) {
        int nh = n, sz = vec[x].size();
        for(int i = cur[x]; i < sz; ++i) {
            auto &e = vec[x][i];
            if(e.c > 0) {
                if(h[x] == h[e.to]+1) {
                    pushFlow(x, e, min(ov[x], e.c));
                    if(ov[x] == 0) { cur[x] = i;  return ; }
                } else nh = min(nh, h[e.to]+1);
            }
        }
        for(int i = 0; i < cur[x]; ++i) {
            auto &e = vec[x][i];
            if(e.c > 0) { nh = min(nh, h[e.to]+1); }
        }
        cur[x] = 0;
        ++workcnt;
        if(~gapNxt[gap[h[x]]])  setHeight(x, nh);
        else {
            int oldh = h[x];
            for(int i = oldh; i <= maxgaph; ++i) {
                for(int j = gap[i]; ~j; j = gapNxt[j])  h[j] = n;
                gap[i] = -1;
            }
            maxgaph = oldh-1;
        }
    }
    void globalRelabel() {
        workcnt = maxh = maxgaph = 0;
        fill(h.begin(), h.end(), n);  h[t] = 0;
        fill(gapPrv.begin(), gapPrv.end(), -1);
        fill(gapNxt.begin(), gapNxt.end(), -1);
        fill(gap.begin(), gap.end(), -1);
        fill(ovList.begin(), ovList.end(), -1);
        fill(ovNxt.begin(), ovNxt.end(), -1);
        fill(cur.begin(), cur.end(), 0);
        queue<int> que;  que.push(t);
        int x;
        while(!que.empty()) {
            x = que.front();  que.pop();
            for(auto &e: vec[x]) {
                if(h[e.to] == n && e.to != s && vec[e.to][e.rev].c > 0) {
                    setHeight(e.to, h[x]+1);
                    que.push(e.to);
                }
            }
        }
    }
    void setHeight(int x, int newh) {
        if(~gapPrv[x]) {
            if(gapPrv[x] == x) {
                gapPrv[gapNxt[x]] = gapNxt[x];
                gap[h[x]] = gapNxt[x];
            } else {
                gapNxt[gapPrv[x]] = gapNxt[x];
                if(~gapNxt[x])  gapPrv[gapNxt[x]] = gapPrv[x];
            }
        }
        if((h[x] = newh) >= n)  return ;
        maxgaph = max(maxgaph, h[x]);
        if(ov[x] > 0) { maxh = max(maxh, h[x]);  ovNxt[x] = ovList[h[x]];  ovList[h[x]] = x; }
        if(~(gapNxt[x] = gap[h[x]]))  gapPrv[gapNxt[x]] = x;
        gap[h[x]] = gapPrv[x] = x;
    }
    void pushFlow(int from, Edge &e, Qint flow) {
        if(!ov[e.to] && e.to != t) {
            ovNxt[e.to] = ovList[h[e.to]];
            ovList[h[e.to]] = e.to;
        }
        e.c -= flow;
        vec[e.to][e.rev].c += flow;
        ov[from] -= flow;
        ov[e.to] += flow;
    }
};
mainint main(){
	qwq
	int n,m,s,t;
	cin>>n>>m>>s>>t;
	HLPP dinic(n,m,s,t);
	for(int i=1,u,v,w;i<=m;++i){
		cin>>u>>v>>w;
		dinic.addedge(u,v,w);
	}
	cout<<dinic.maxflow();
}
/*
struct HLPP {
    using Qint = long long;
    struct Edge{int to;Qint c;int rev;Edge(int to,Qint c,int rev):to(to),c(c),rev(rev){}};int n,m,s,t;int maxh,maxgaph,workcnt;vector<vector<Edge>>vec;vector<Qint>ov;vector<int>h;vector<int>cur;vector<int>ovList,ovNxt;vector<int>gap,gapPrv,gapNxt;HLPP(int n,int m,int s,int t):n(n),m(m),s(s),t(t),maxh(0),maxgaph(0),workcnt(0),vec(n+1),ov(n+1),h(n+1),cur(n+1),ovList((n+1),-1),ovNxt(n+1,-1),gap((n+1),-1),gapPrv(n+1,-1),gapNxt(n+1,-1){}void addedge(int u,int v,Qint c){vec[u].push_back(Edge(v,c,vec[v].size()));vec[v].push_back(Edge(u,0,vec[u].size()-1));}Qint maxflow(){globalRelabel();for(auto&e:vec[s])if(e.c){pushFlow(s,e,e.c);maxh=max(maxh,h[e.to]);}for(;maxh>=0;--maxh){while(~ovList[maxh]){int x=ovList[maxh];ovList[maxh]=ovNxt[x];discharge(x);if(workcnt>(n<<2))globalRelabel();}}return ov[t];}private:void discharge(int x){int nh=n,sz=vec[x].size();for(int i=cur[x];i<sz;++i){auto&e=vec[x][i];if(e.c>0){if(h[x]==h[e.to]+1){pushFlow(x,e,min(ov[x],e.c));if(ov[x]==0){cur[x]=i;return;}}else nh=min(nh,h[e.to]+1);}}for(int i=0;i<cur[x];++i){auto&e=vec[x][i];if(e.c>0){nh=min(nh,h[e.to]+1);}}cur[x]=0;++workcnt;if(~gapNxt[gap[h[x]]])setHeight(x,nh);else{int oldh=h[x];for(int i=oldh;i<=maxgaph;++i){for(int j=gap[i];~j;j=gapNxt[j])h[j]=n;gap[i]=-1;}maxgaph=oldh-1;}}void globalRelabel(){workcnt=maxh=maxgaph=0;fill(h.begin(),h.end(),n);h[t]=0;fill(gapPrv.begin(),gapPrv.end(),-1);fill(gapNxt.begin(),gapNxt.end(),-1);fill(gap.begin(),gap.end(),-1);fill(ovList.begin(),ovList.end(),-1);fill(ovNxt.begin(),ovNxt.end(),-1);fill(cur.begin(),cur.end(),0);queue<int>que;que.push(t);int x;while(!que.empty()){x=que.front();que.pop();for(auto&e:vec[x]){if(h[e.to]==n&&e.to!=s&&vec[e.to][e.rev].c>0){setHeight(e.to,h[x]+1);que.push(e.to);}}}}void setHeight(int x,int newh){if(~gapPrv[x]){if(gapPrv[x]==x){gapPrv[gapNxt[x]]=gapNxt[x];gap[h[x]]=gapNxt[x];}else{gapNxt[gapPrv[x]]=gapNxt[x];if(~gapNxt[x])gapPrv[gapNxt[x]]=gapPrv[x];}}if((h[x]=newh)>=n)return;maxgaph=max(maxgaph,h[x]);if(ov[x]>0){maxh=max(maxh,h[x]);ovNxt[x]=ovList[h[x]];ovList[h[x]]=x;}if(~(gapNxt[x]=gap[h[x]]))gapPrv[gapNxt[x]]=x;gap[h[x]]=gapPrv[x]=x;}void pushFlow(int from,Edge&e,Qint flow){if(!ov[e.to]&&e.to!=t){ovNxt[e.to]=ovList[h[e.to]];ovList[h[e.to]]=e.to;}e.c-=flow;vec[e.to][e.rev].c+=flow;ov[from]-=flow;ov[e.to]+=flow;}
};
*/