#include <iostream>
#include <algorithm>
#include <string>
#include <set>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <map>
#include <queue>
#include <vector>
using namespace std;
//
#define IOS ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define ios ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define qwq ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define QWQ ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define jump ;return 0;
using mainint=signed;using ll=long long;using ull=unsigned long long;using ld=long double;template<class T>void gmin(T &a,T b){if(a>b) a=b;}template<class T>void gmax(T &a,T b){if(a<b) a=b;}using pii=pair<int,int>;using pll=pair<ll,ll>;using pil=pair<int,ll>;using Pli=pair<ll,int>;const int INF=0x3f3f3f3f;const ll INFINF=0x3f3f3f3f3f3f3f3f;
//
int n,x[10005],y[10005],w[10005];
#define double long double
double ansx,ansy,best=1e20;
double getd(double _x,double _y){
	double sum=0;
	for(int i=1;i<=n;++i){
		sum+=sqrt((x[i]-_x)*(x[i]-_x)+(y[i]-_y)*(y[i]-_y))*w[i];
	}
	if(sum<best){
		ansx=_x,ansy=_y;best=sum;
	}
	return sum;
}
double ran(){
	return rand()*1.0/RAND_MAX;
}
double ran2(){
	return (rand()*1.0/RAND_MAX)*2-1;
}
void fwgghack(double nowx,double nowy){
	double t=100000;
	while(t>=0.001){
		double tox=nowx+t*ran2(),toy=nowy+t*ran2();
		double delta=getd(tox,toy)-getd(nowx,nowy);
		if(exp(-delta/t)>ran()) nowx=tox,nowy=toy;
		t*=0.98;
	}
	for(int i=1;i<=1000;++i){
		double tox=ansx+t*ran2(),toy=ansy+t*ran2();
		getd(tox,toy);
	}
}
mainint main(){
	qwq
	cin>>n;
	srand(time(0));
	for(int i=1;i<=n;++i) cin>>x[i]>>y[i]>>w[i];
	for(int i=1;i<=n;++i) ansx+=x[i];
	for(int i=1;i<=n;++i) ansy+=y[i];
	ansx/=n,ansy/=n;
	best=getd(ansx,ansy);
	double tx=ansx,ty=ansy;
	while((double)clock()/CLOCKS_PER_SEC < 0.900){
		double i=ran2()*8000;
		double ax=tx+i*ran(),ay=ty+i*ran();
		fwgghack(ax,ay);
	}
	cout<<fixed<<setprecision(3)<<ansx<<" "<<ansy;
}