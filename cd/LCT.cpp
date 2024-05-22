#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
int sta[100005];
struct node{
	int son[2],fa,v,xorsum,lazy;
}t[100005];
bool notroot(int p){
	return p==t[t[p].fa].son[0] || p==t[t[p].fa].son[1];
}
void update(int p){
	t[p].xorsum=t[t[p].son[0]].xorsum^t[t[p].son[1]].xorsum^t[p].v;
}
void spreadr(int p){
	swap(t[p].son[0],t[p].son[1]);t[p].lazy^=1;
}
void spread(int p){
	if(t[p].lazy){
		if(t[p].son[0]) spreadr(t[p].son[0]);
		if(t[p].son[1]) spreadr(t[p].son[1]);
		t[p].lazy=0;
	}
}
void rotate(int p){
	int fa=t[p].fa,fafa=t[fa].fa;
	int k=(t[fa].son[1]==p),w=t[p].son[!k];
	if(notroot(fa)) t[fafa].son[t[fafa].son[1]==fa]=p;
	t[p].son[!k]=fa;
	t[fa].son[k]=w;
	if(w) t[w].fa=fa;
	t[fa].fa=p;//IMPORTANT
	t[p].fa=fafa;//IMPORTANT
	update(fa);
}
void splay(int p){
	int temp=p,top=0;
	sta[++top]=temp;
	while(notroot(temp)) sta[++top]=temp=t[temp].fa;
	while(top){spread(sta[top--]);}
	while(notroot(p)){
		int fa=t[p].fa,fafa=t[fa].fa;
		if(notroot(fa)) rotate((t[fa].son[0]==p)^(t[fafa].son[0]==fa)?p:fa);
		rotate(p);
	}
	update(p);
}
void access(int p){
	for(int y=0;p;y=p,p=t[p].fa){
		splay(p);t[p].son[1]=y;update(p);
	}
}
void makeroot(int p){
	access(p);splay(p);spreadr(p);
}
int findroot(int p){
	access(p);splay(p);
	while(t[p].son[0]) spread(p),p=t[p].son[0];
	splay(p);return p;
}
//q is the root now
void split(int p,int q)
{makeroot(p);access(q);splay(q);}
bool link(int p,int q){//p.father points to q
	makeroot(p);if(findroot(q)==p)return 0;//failed illegal
	t[p].fa=q;return 1;
}
bool cut(int p,int q){
	makeroot(p);
	if(findroot(q)!=p || t[q].fa!=p || t[q].son[0]) return 0;
	t[q].fa=t[p].son[1]=0;
	update(p);return 1;
}
signed main(){
	//qwq
	int n,m,op,x,y;
	cin>>n>>m;
	for(int i=1;i<=n;++i) cin>>t[i].v;
	while(m--){
		cin>>op>>x>>y;
		if(op==0){split(x,y);cout<<t[y].xorsum<<'\n';}
		else if(op==1){link(x,y);}
		else if(op==2){cut(x,y);}
		else if(op==3){splay(x);t[x].v=y;}
	}
}