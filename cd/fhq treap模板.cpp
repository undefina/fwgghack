#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cstdlib>
using namespace std;
struct node
{
	int l,r,key,val,size;
}t[200005];
int idx=0,dl,dr,root;
int getval(int key)
{
	t[++idx].key=key;
	t[idx].val=rand();
	t[idx].size=1;
	return idx;
}
void update(int p)
{
	t[p].size=t[t[p].l].size+t[t[p].r].size+1;
}
void split(int p,int key,int &l,int &r)
{
	if(!p){
		l=r=0;
		return;
	}
	if(t[p].key<=key){
		l=p;
		split(t[l].r,key,t[l].r,r);
	}
	else{
		r=p;
		split(t[r].l,key,l,t[r].l);
	}
	update(p);
}
int merge(int p,int q)
{
	if(!p || !q) return p|q;
	if(t[p].val<=t[q].val){
		t[p].r=merge(t[p].r,q);
		update(p);
		return p;
	}
	else{
		t[q].l=merge(p,t[q].l);
		update(q);
		return q;
	}
}
void ins(int key)
{
	split(root,key-1,dl,dr);
	root=merge(merge(dl,getval(key)),dr);
}
void del(int key)
{
	int mid=0;
	split(root,key-1,dl,dr);
	split(dr,key,mid,dr);
	mid=merge(t[mid].l,t[mid].r);
	root=merge(dl,merge(mid,dr));
}
int getrank(int key)
{
	split(root,key-1,dl,dr);
	int ans=t[dl].size+1;
	root=merge(dl,dr);
	return ans;
}
int getnum(int p,int key)
{
	if(!key) return 0;
	int siz=t[t[p].l].size+1;
	if(siz==key) return p;//t[p].key?
	if(siz>key) return getnum(t[p].l,key);
	else return getnum(t[p].r,key-siz);
}
int pre(int key){
	split(root,key-1,dl,dr);
	int ans=getnum(dl,t[dl].size);
	root=merge(dl,dr);
	return ans;
}
int nxt(int key){
	split(root,key,dl,dr);
	int ans=getnum(dr,1);
	root=merge(dl,dr);
	return ans;
}
int main()
{
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int n,op,_;
	cin>>_;
	while(_--){
		cin>>op>>n;
		if(op==1) ins(n);
		else if(op==2) del(n);
		else if(op==3) cout<<getrank(n)<<'\n';
		else if(op==4) cout<<getnum(root,n)<<'\n';
		else if(op==5){
			split(root,n-1,dl,dr);
			cout<<getnum(dl,t[dl].size)<<'\n';
			root=merge(dl,dr);
		}
		else{
			split(root,n,dl,dr);
			cout<<getnum(dr,1)<<'\n';
			root=merge(dl,dr);
		}
	}
}