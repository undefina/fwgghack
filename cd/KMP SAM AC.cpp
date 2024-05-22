#include <bits/stdc++.h>
using namespace std;
string s1,s2;
int nxt[1000005];
void getnext(string &s,int *nxt){
	int len=s.size();
	nxt[0]=-1;
	int k=-1;
	for(int q=1;q<len;++q){
		while(k>-1 && s[k+1]!=s[q]) k=nxt[k];
		if(s[k+1]==s[q]) k++;
		nxt[q]=k;
	}
}
void KMP(string &s1,string &s2,int *nxt){
	int len1=s1.length(),len2=s2.length();
	getnext(s2,nxt);
	int k=-1;
	for(int q=0;q<len1;++q){
		while(k!=-1 && s2[k+1]!=s1[q]) k=nxt[k];
		if(s2[k+1]==s1[q]) k++;
		if(k==len2-1){
			cout<<q-len2+1+1<<'\n';
			k=nxt[k];
		}
	}
}
/*
//exKMP
int nxt[1000005];//length,no need to -1
void getexnext(string &s,int *nxt){
	int len=s.length();
	nxt[0]=len;
	int j=0;
	while(j<len && s[j]==s[j+1]) j++;
	nxt[1]=j;
	for(int k=2,j=1,L,p;k<len;++k){
		p=j+nxt[j]-1;L=nxt[k-j];
		if(p<=k+L-1){
			int i=(p>=k ? p-k+1 : 0);
			while(k+i<len && s[k+i]==s[i]) i++;
			nxt[k]=i;
			j=k;
		}
		else nxt[k]=L;
	}
}
int extend[1000005];
void exKMP(string &s1,string &s2,int *nxt,int *extend){
	int len1=s1.length(),len2=s2.length();
	int j=0;
	while(j<len1 && j<len2 && s1[j]==s2[j]) j++;
	extend[0]=j;
	getexnext(s2,nxt);
	for(int k=1,j=0,L,p;k<len1;++k){
		p=j+extend[j]-1;L=nxt[k-j];
		if(p<=k+L-1){
			int i=(p>=k ? p-k+1 : 0);
			while(k+i<len1 && i<len2 && s1[k+i]==s2[i]) i++;
			extend[k]=i;
			j=k;
		}
		else extend[k]=L;
	}
}
*/

/*
//manacher
string transform(string &s){
	string ans="^";
	for(char c:s) ans+='@',ans+=c;
	ans+='@';
	return ans;
}
int Rad[1000005];
void manacher(string &s,int *Rad){
	string t=transform(s);
	int r=0,mid=0,len=t.length()-1;
	int ans=0;
	for(int i=1;i<len;++i){
		Rad[i]=(r>i ? min(Rad[2*mid-i],r-i) : 1);
		while(t[i+Rad[i]]==t[i-Rad[i]]) Rad[i]++;
		if(i+Rad[i]>r){
			r=i+Rad[i];
			mid=i;
		}
		gmax(ans,Rad[i]-1);
	}
	cout<<ans;
	//for(int i=2;i<=n+n;i++) cout<<Rad[i]-1<<space;
}
*/

/*
//AC
int trie[1000005][26],fail[1000005],idx=0,endstr[1000005];
void ins(string &s){
	int len=s.length(),p=0;
	for(int i=0;i<len;++i){
		int temp=s[i]-'a';
		if(trie[p][temp]==0) trie[p][temp]=++idx;
		p=trie[p][temp];
	}
	endstr[p]++;
}
void buildAC(){
	fail[0]=0;
	queue<int> que;
	for(int i=0;i<26;++i){
		if(trie[0][i]){
			que.push(trie[0][i]);
		}
	}
	while(!que.empty()){
		int u=que.front();
		que.pop();
		for(int i=0;i<26;++i){
			if(trie[u][i]){
				fail[trie[u][i]]=trie[fail[u]][i];
				que.push(trie[u][i]);
			}
			else trie[u][i]=trie[fail[u]][i];
		}
	}
}
bool used[1000005];
int query(string &s){
	int ans=0,p=0,len=s.length();
	for(int i=0;i<len;++i){
		p=trie[p][s[i]-'a'];
		for(int j=p;!used[j] && j!=0;j=fail[j]){
			ans+=endstr[j];
			used[j]=1;
		}
	}
	return ans;
}
*/

/*
//SA
int sa[1000005],c[1000005],tp[1000005],rk[1000005];
void getSA(int m,string &s){//s starts from 0
	int n=s.length();
    for(int i=1;i<=m;i++) c[i]=0;
    for(int i=1;i<=n;i++) c[rk[i]=s[i-1]]++;
    for(int i=2;i<=m;i++) c[i]+=c[i-1];
    for(int i=n;i>=1;i--) sa[c[rk[i]]--]=i;
    for(int k=1;k<=n;k*=2){
        int p=1;
        for(int i=n-k+1;i<=n;i++) tp[p++]=i;
        for(int i=1;i<=n;i++)
            if(sa[i]>k)
            	tp[p++]=sa[i]-k;
        for(int i=1;i<=m;i++) c[i]=0;
        for(int i=1;i<=n;i++) c[rk[i]]++;
        for(int i=2;i<=m;i++) c[i]+=c[i-1];
        for(int i=n;i>=1;i--) sa[c[rk[tp[i]]]--]=tp[i];
        tp[sa[1]]=p=1;
        for(int i=2;i<=n;i++){
			p+=((rk[sa[i]]==rk[sa[i-1]] && ((sa[i]+k>n?-1:rk[sa[i]+k])==(sa[i-1]+k>n?-1:rk[sa[i-1]+k])))?0:1);
            tp[sa[i]]=p;
        }
        swap(rk,tp);
        if(p>=n) break;
        m=p;
    }
}
int height[1000005];
void getHeight(string &s){
	int n=s.length();
	for(int i=1,k=0;i<=n;++i){
		if(k) --k;
		while(s[i+k-1]==s[sa[rk[i]-1]+k-1]) k++;
		height[rk[i]]=k;
	}
}
*/
/*
//SAM
struct sam_node{
    int len,link;
    int to[26];
};
sam_node t[2000005];//*2
int sam_size,last;
void sam_init(){
    sam_size++;
    last=1;
}
int cnt[2000005];
void sam_extend(char c){
    int p=last;
    int np=++sam_size;
    last=np;
    cnt[np]=1;
    t[np].len=t[p].len+1;
    for(;p && !t[p].to[c-'a'];p=t[p].link)
        t[p].to[c-'a']=np;
    if(!p) t[np].link=1;
    else{
        int q=t[p].to[c-'a'];
        if(t[q].len==t[p].len+1) t[np].link=q;
        else{
            int nq=++sam_size;
            t[nq]=t[q];
            t[nq].len=t[p].len+1;
            t[q].link=nq;
            t[np].link=nq;
            for(;p && t[p].to[c-'a']==q;p=t[p].link) t[p].to[c-'a']=nq;
        }
    }
}
void LCS(string &s){
    int ans=0;
    int p=1,len=0;
    for(char c:s){
        while(p!=1 && !t[p].to[c-'a']){
            p=t[p].link;
            len=t[p].len;
        }
        if(t[p].to[c-'a']){
            p=t[p].to[c-'a'];
            len++;
        }
        gmax(ans,len);
    }
    cout<<ans;
}
*/

/*
//exSAM
struct sam_node{
    int len,link;
    int to[26];
};
sam_node t[2000005];//*2
int sam_size,last;
void sam_init(){
    sam_size++;
    last=1;
}
int cnt[2000005];
int sam_extend(char c,int _last,int *cnt){
    if(t[_last].to[c-'a']){
        int p=_last,q=t[p].to[c-'a'];
        if(t[p].len+1==t[q].len){cnt[q]++;return q;}
        int nq=++sam_size;
        t[nq]=t[q];
        t[nq].len=t[p].len+1;
        t[nq].link=t[q].link;
        t[q].link=nq;
        for(;p && t[p].to[c-'a']==q;p=t[p].link) t[p].to[c-'a']=nq;
        cnt[nq]++;
        return nq;
    }
    int p=_last;
    int np=++sam_size;
    cnt[np]++;
    t[np].len=t[p].len+1;
    for(;p && !t[p].to[c-'a'];p=t[p].link)
        t[p].to[c-'a']=np;
    if(!p) t[np].link=1;
    else{
        int q=t[p].to[c-'a'];
        if(t[q].len==t[p].len+1) t[np].link=q;
        else{
            int nq=++sam_size;
            t[nq]=t[q];
            t[nq].len=t[p].len+1;
            t[q].link=nq;
            t[np].link=nq;
            for(;p && t[p].to[c-'a']==q;p=t[p].link) t[p].to[c-'a']=nq;
        }
    }
    return np;
}
void exSAM_expand(string &s){
    last=1;
    for(char c:s) last=sam_extend(c,last);
}
//WARNING:BE CAREFUL WHEN EXPANDING
//for(int i=1;i<=n;++i){
//        string s;
//        cin>>s;
//        last=1;
//        for(char c:s) last=sam_extend(c,last);
//    }
*/

/*
//PAM
int sz,tot,last;
long long cnt[500005],zcnt[500005];
int t[500005][27],len[500005],fail[500005],trans[500005];
char s[500005];
int node(int l){
    sz++;
    // memset(t[sz],0,sizeof(t[sz]));
    // len[sz]=l;
    // fail[sz]=cnt[sz]=zcnt[sz]=0;
    return sz;
}
void pam_init(){
    sz=-1;
    last=0;
    s[tot=0]='^';
    node(0);
    node(-1);
    fail[0]=1;
}
int getfail(int x){
    while (s[tot-len[x]-1]!=s[tot]) x=fail[x];
    return x;
}
int gettrans(int x,int p){
    while (s[tot-len[x]-1]!=s[tot] || (len[x]+2)*2>len[p]) x=fail[x];
    return x;
}
void insert(char c){
    s[++tot]=c;
    int p=getfail(last);
    if (!t[p][c-'0']) {
        int x=node(len[p] + 2);
        fail[x]=t[getfail(fail[p])][c-'0'];
        t[p][c-'0']=x;
        if(len[x]<=2) trans[x]=fail[x];
        else trans[x]=t[gettrans(trans[p],x)][c-'a'];
    }
    last=t[p][c-'0'];
    cnt[last]++;
}
*/