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
using mainint = signed;using ll = long long;using ull = unsigned long long;using ld = long double;
template<class T>void gmin(T &a,T b){if(a>b) a=b;}
template<class T>void gmax(T &a,T b){if(a<b) a=b;};using pll=pair<ll,ll>;using pil=pair<int,ll>;using Pli=pair<ll,int>;const int INF=0x3f3f3f3f;const ll INFINF=0x3f3f3f3f3f3f3f3f;

struct node{
	int x1,x2,y1,y2,id;
}t[100005<<2];
struct dian{
	int x,y,id;
}point[100005];
bool cmpx(dian a,dian b){return a.x<b.x;}
bool cmpy(dian a,dian b){return a.y<b.y;}

void update(int p){
	t[p].x1=min(t[p*2].x1,t[p*2+1].x1);
	t[p].x2=max(t[p*2].x2,t[p*2+1].x2);
	t[p].y1=min(t[p*2].y1,t[p*2+1].y1);
	t[p].y2=max(t[p*2].y2,t[p*2+1].y2);
	t[p].id=min(t[p*2].id,t[p*2+1].id);
}
void build(int p,int l,int r,int kd){
	if(l==r){
		t[p].x1=t[p].x2=point[l].x;
		t[p].y1=t[p].y2=point[l].y;
		t[p].id=point[l].id;
		return;
	}
	int mid=(l+r)/2;
	nth_element(point+l,point+mid,point+r+1,kd ? cmpx : cmpy);
	build(p*2,l,mid,kd^1);
	build(p*2+1,mid+1,r,kd^1);
	update(p);
}
void modify(int p,int l,int r,int x){
	if(l==r){
		t[p].id=INF;
		return;
	}
	int mid=(l+r)/2;
	if(x<=mid) modify(p*2,l,mid,x);
	else modify(p*2+1,mid+1,r,x);
	update(p);
}
node kde;
void query(int p){
	if(t[p].id>=kde.id || t[p].x1>kde.x2 || t[p].x2<kde.x1 || t[p].y1>kde.y2 || t[p].y2<kde.y1) return;
	if(t[p].x1>=kde.x1 && t[p].x2<=kde.x2 && t[p].y1>=kde.y1 && t[p].y2<=kde.y2){
		gmin(kde.id,t[p].id);
		return;
	}
	if(t[p*2].id<t[p*2+1].id) query(p*2),query(p*2+1);
	else query(p*2+1),query(p*2);
}

struct sq{
	int x1,x2,y1,y2,h,id;
}S[100005];
bool operator <(sq a,sq b){
	return a.h<b.h;
}

int ans[100005];
mainint main(){
	qwq
	int n,m;
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>S[i].x1>>S[i].x2>>S[i].y1>>S[i].y2>>S[i].h;
		S[i].id=i;
	}
	sort(S+1,S+1+n);
	cin>>m;
	for(int i=1;i<=m;++i){
		cin>>point[i].x>>point[i].y;
		point[i].id=i;
	}
	build(1,1,m,0);
	vector<int> rev(100005,0);
	for(int i=1;i<=m;++i) rev[point[i].id]=i;//知道了一个点是kdt的第几个叶子，方便单点修改。
	for(int i=1;i<=n;++i){
		kde={S[i].x1,S[i].x2,S[i].y1,S[i].y2,INF};
		query(1);
		if(kde.id>m) continue;
		ans[kde.id]=S[i].id;
		modify(1,1,m,rev[kde.id]);//建树过程中会打乱点的顺序！
	}
	for(int i=1;i<=m;++i) cout<<ans[i]<<'\n';
}