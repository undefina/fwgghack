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

struct dian{
	int x,y,val;
}point[200005];
bool cmpx(dian a,dian b){return a.x<b.x;}
bool cmpy(dian a,dian b){return a.y<b.y;}

struct node{
	int l,r,x1,x2,y1,y2,sum,siz;
	dian np;
}t[200005];
node getkde(int x1,int x2,int y1,int y2){
	node kde;
	kde.x1=x1,kde.x2=x2,kde.y1=y1,kde.y2=y2;
	return kde;
}
int rubbish[200005],top,ridx,pidx;
int newnode(){
	if(top) return rubbish[top--];
	return ++ridx;
}

void update(int p){
	t[p].x1=t[p].x2=t[p].np.x;
	t[p].y1=t[p].y2=t[p].np.y;
	if(t[p].l){
		gmin(t[p].x1,t[t[p].l].x1);
		gmax(t[p].x2,t[t[p].l].x2);
		gmin(t[p].y1,t[t[p].l].y1);
		gmax(t[p].y2,t[t[p].l].y2);
	}
	if(t[p].r){
		gmin(t[p].x1,t[t[p].r].x1);
		gmax(t[p].x2,t[t[p].r].x2);
		gmin(t[p].y1,t[t[p].r].y1);
		gmax(t[p].y2,t[t[p].r].y2);
	}
	t[p].sum=t[p].np.val+t[t[p].l].sum+t[t[p].r].sum;
	t[p].siz=1+t[t[p].l].siz+t[t[p].r].siz;
}

void tosequence(int p){
	if(p==0) return;
	point[++pidx]=t[p].np;
	rubbish[++top]=p;
	tosequence(t[p].l);
	tosequence(t[p].r);
}

int rebuild(int l,int r,int kd){
	if(l>r) return 0;
	int mid=(l+r)/2;
	int p=newnode();
	nth_element(point+l,point+mid,point+1+r,kd ? cmpy : cmpx);
	t[p].np=point[mid];
	t[p].l=rebuild(l,mid-1,kd^1);
	t[p].r=rebuild(mid+1,r,kd^1);
	update(p);
	return p;
}

const double hope=0.6;
void isgood(int &p,int d){
	if(t[t[p].l].siz>hope*t[p].siz || t[t[p].r].siz>hope*t[p].siz){
		pidx=0;
		tosequence(p);
		p=rebuild(1,t[p].siz,d);
	}
}

void ins(int &p,int kd,dian np){
	if(p==0){
		p=newnode();
		t[p].l=t[p].r=0;
		t[p].np=np;
		update(p);
		return;
	}
	if(kd ? np.y<=t[p].np.y : np.x<=t[p].np.x) ins(t[p].l,kd^1,np);
	else ins(t[p].r,kd^1,np);
	update(p);
	isgood(p,kd);
}

int query(int p,node kde){
	if(p==0) return 0;
	if(t[p].x1>kde.x2 || t[p].x2<kde.x1 || t[p].y1>kde.y2 || t[p].y2<kde.y1) return 0;
	if(t[p].x1>=kde.x1 && t[p].x2<=kde.x2 && t[p].y1>=kde.y1 && t[p].y2<=kde.y2){
		return t[p].sum;
	}
	//NOTICE MYSELF
	int ans=0;
	if(t[p].np.x>=kde.x1 && t[p].np.x<=kde.x2 && t[p].np.y>=kde.y1 && t[p].np.y<=kde.y2){
		ans+=t[p].np.val;
	}
	ans+=query(t[p].l,kde);
	ans+=query(t[p].r,kde);
	return ans;
}
mainint main(){
	qwq
	int n;
	cin>>n;
	int last=0;
	int root=0;
	while(1){
		int op,x1,y1,x2,y2,v;
		cin>>op;
		if(op==1){
			cin>>x1>>y1>>v;
			x1^=last,y1^=last,v^=last;
			ins(root,0,{x1,y1,v});
		}
		else if(op==2){
			cin>>x1>>y1>>x2>>y2;
			x1^=last;x2^=last;y1^=last;y2^=last;
			last=query(root,getkde(x1,x2,y1,y2));
			cout<<last<<'\n';
		}
		else break;
	}
}