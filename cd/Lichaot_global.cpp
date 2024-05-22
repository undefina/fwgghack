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

int n;
struct Line{
	double k,b;
}tag[100005<<2];int idx;
double getval(int x,int id){
	// if(id==0) return INFINF;//IMPORTANT
	return tag[id].k*(x)+tag[id].b;
}
struct node{
	int id;
}t[100005<<2];
void modify(int p,int l,int r,int id){
	if(l==r){
		if(getval(l,id)>getval(l,t[p].id)) t[p].id=id;
		return ;
	}
	int mid=(l+r)>>1;
	if(tag[id].k>tag[t[p].id].k){
		if(getval(mid,id)>getval(mid,t[p].id)) modify(p*2,l,mid,t[p].id),t[p].id=id;
		else modify(p*2+1,mid+1,r,id);
	}else{
		if(getval(mid,id)>getval(mid,t[p].id)) modify(p*2+1,mid+1,r,t[p].id),t[p].id=id;
		else modify(p*2,l,mid,id);
	}
}
void addedge(double k,double b){
	tag[++idx]={k,b};
	modify(1,1,100000,idx);
}
double query(int p,int l,int r,int x){
	if(l==r) return getval(x,t[p].id);
	int mid=(l+r)/2;
	double ans=getval(x,t[p].id);
	if(x<=mid) gmax(ans,query(p*2,l,mid,x));
	else gmax(ans,query(p*2+1,mid+1,r,x));
	return ans;
}
mainint main(){
    qwq
	cin>>n;
	string s;
	for(int i=1;i<=n;++i){
		cin>>s;
		if(s[0]=='P'){
			double a,b;
			cin>>a>>b;
			addedge(b,a);
		}
		else{
			int x;
			cin>>x;
			cout<<(int)(query(1,1,100000,x)/100)<<'\n';
		}
	}
}