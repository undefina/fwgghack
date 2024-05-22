#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define FOR() ll le=e[u].size();for(ll i=0;i<le;i++)
#define QWQ cout<<"QwQ\n";
#define ll long long
#include <vector>
#include <queue>
#include <map>
#define ls son[x][0]
#define rs son[x][1]

using namespace std;
const ll N=801010;
const ll qwq=303030;
const ll inf=0x3f3f3f3f3f3f3f3f;

ll Q;
ll n,m,tot;
ll a[N];
ll fu;
ll rt,fa[N],son[N][2],siz[N],num[N],val[N],sum[N];

inline ll read() {
    ll sum1 = 0, ff = 1; char c = getchar();
    while(c<'0' || c>'9') { if(c=='-') ff = -1; c = getchar(); }
    while(c>='0'&&c<='9') { sum1 = sum1 * 10 + c - '0'; c = getchar(); }
    return sum1 * ff;
}

inline ll touhou(ll x) { return son[fa[x]][1]==x; }
inline void pushup(ll x) { siz[x] = siz[ls] + siz[rs] + num[x]; sum[x] = sum[ls] + sum[rs] + num[x] * val[x]; }
inline void rotate(ll x) {
    ll y = fa[x], z = fa[y], k = touhou(x), w = son[x][k^1];
    son[z][touhou(y)] = x; son[x][k^1] = y; son[y][k] = w;
    fa[w] = y; fa[y] = x; fa[x] = z; pushup(y); pushup(x);
}
inline void splay(ll x,ll goal) {
    while(fa[x]!=goal) {
        ll y = fa[x], z = fa[y];
        if(z!=goal) {
            if(touhou(y)==touhou(x)) rotate(y);
            else rotate(x);
        }
        rotate(x);
    }
    if(!goal) rt = x;
}

inline void insert(ll v) {
    ll x = rt, f = 0;
    while(val[x]!=v && x)
        f = x, x = son[x][val[x]<v];
    if(x) num[x]++, pushup(x);
    else {
        x = ++tot;
        if(f) son[f][val[f]<v] = x;
        fa[x] = f; siz[x] = num[x] = 1;
        val[x] = sum[x] = v;
    }
    splay(x,0);
}

inline void find(ll v) {
    ll x = rt;
    while(val[x]!=v && son[x][ val[x]<v ])
        x = son[x][ val[x]<v ];
    splay(x,0); 
}
inline ll qian(ll v) {
    find(v);
    if(val[rt]<v) return rt;
    ll x = son[rt][0];
    while(rs) x = rs; return x;
}
inline ll hou(ll v) {
    find(v);
    if(val[rt]>v) return rt;
    ll x = son[rt][1];
    while(ls) x = ls; return x;
}

void del(ll v) {
    ll y = qian(v), x = hou(v);
    splay(y,0); splay(x,y);
    if(num[ls]>1) num[ls]--, siz[ls]--, sum[ls]-=val[ls];
    else ls = 0;
    pushup(x); pushup(y);
}

inline ll query(ll v) {
    if(!fu) return 0;
    ll x = rt;
    while(1) {
        if(sum[ls]>=v) x = ls;
        else if(sum[ls]+val[x]*num[x]<v) v -= sum[ls]+val[x]*num[x], x = rs;
        else {v -= sum[ls]; break;}
    }
    splay(x,0);
    ll res = siz[ls]-1;
    res += v/val[rt];
    return res;
}

int main() {
    ll x,wei;
    insert(inf); insert(0);
    n = read(); Q = read();
    for(ll i=1;i<=n;i++) {
        a[i] = read();
        if(a[i]>0) insert(a[i]);
        else fu -= a[i];
    }
    while(Q--) {
        wei = read(); x = read();
        if(a[wei]<=0) fu += a[wei];
        else del(a[wei]);
        if(x<=0) fu -= x;
        else insert(x);
        a[wei] = x;
        // outing();
        cout<<query(fu)+1<<"\n";
    }
    return 0;
}