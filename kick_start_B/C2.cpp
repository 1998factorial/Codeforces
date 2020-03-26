//#pragma comment(linker, "/stack:200000000")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize(3)
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
//#pragma GCC target("sse3","sse2","sse")
//#pragma GCC target("avx","sse4","sse4.1","sse4.2","ssse3")
//#pragma GCC target("f16c")
//#pragma GCC optimize("inline","fast-math","unroll-loops","no-stack-protector")
//#pragma GCC diagnostic error "-fwhole-program"
//#pragma GCC diagnostic error "-fcse-skip-blocks"
//#pragma GCC diagnostic error "-funsafe-loop-optimizations"
//#pragma GCC diagnostic error "-std=c++14"
#include<cstdio>
#include<cstring>
#include<iostream>
#include <complex>
#include <vector>
using namespace  std;

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
//#include "ext/pb_ds/tree_policy.hpp"
//#include "ext/pb_ds/assoc_container.hpp"
#define PB push_back
#define PF push_front
#define LB lower_bound
#define UB upper_bound
#define fr(x) freopen(x,"r",stdin)
#define fw(x) freopen(x,"w",stdout)
#define iout(x) printf("%d\n",x)
#define lout(x) printf("%lld\n",x)
#define REP(x,l,u) for(ll x = l;x<u;x++)
#define RREP(x,l,u) for(ll x = l;x>=u;x--)
#define complete_unique(a) a.erase(unique(a.begin(),a.end()),a.end())
#define mst(x,a) memset(x,a,sizeof(x))
#define all(a) a.begin(),a.end()
#define PII pair<int,int>
#define PLL pair<ll,ll>
#define MP make_pair
#define sqr(x) ((x)*(x))
#define lowbit(x) ((x)&(-(x)))
#define se second
#define fi first
#define sz(x) ((int)x.size())
#define EX0 exit(0);

typedef  long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ld;
using namespace std;
typedef vector<ll> VLL;
typedef vector<int> VI;
const int block_size = 320;
typedef complex<ll> point;
const ll mod = 1e9+7;
const ld eps = 1e-9;
const db PI = atan(1)*4;
template<typename T>
inline int sign(const T&a) {
    if(a<0)return -1;
    if(a>0)return 1;
    return 0;
}
string to_string(string s) {
    return '"' + s + '"';
}

string to_string(const char* s) {
    return to_string((string) s);
}

string to_string(bool b) {
    return (b ? "true" : "false");
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A>
string to_string(A v) {
    bool first = true;
    string res = "{";
    for (const auto &x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    cerr << " " << to_string(H);
    debug_out(T...);
}

#ifndef ONLINE_JUDGE
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define dbg(...) {}
#endif

template<typename T,typename S>inline bool upmin(T&a,const S&b){return a>b?a=b,1:0;}
template<typename T,typename S>inline bool upmax(T&a,const S&b){return a<b?a=b,1:0;}

template<typename T> inline void in(T &x) {
    x = 0;
    T f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (isdigit(ch))  {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    x *= f;
}

ll twop(int x) {
    return 1LL<<x;
}

template<typename A,typename B > inline void in(A&x,B&y) {
    in(x);
    in(y);
}
template<typename A,typename B,typename C>inline void in(A&x,B&y,C&z) {
    in(x);
    in(y);
    in(z);
}
template<typename A,typename B,typename C,typename D> inline void in(A&x,B&y,C&z,D&d) {
    in(x);
    in(y);
    in(z);
    in(d);
}

#define ls (node<<1)
#define rs (node<<1|1)
using namespace std;
const int N=100005,inf=2e8;
int n,m,a[N];
struct Segtree{
    int max,vl,vr,sum,fg;
}Tree[N<<4];
void updata(int node){
    Tree[node].max=max(Tree[ls].max,max(Tree[rs].max,Tree[ls].vr+Tree[rs].vl));
    Tree[node].sum=Tree[ls].sum+Tree[rs].sum;
    Tree[node].vl=max(Tree[ls].vl,Tree[ls].sum+Tree[rs].vl);
    Tree[node].vr=max(Tree[rs].vr,Tree[rs].sum+Tree[ls].vr);
}
void build(int l,int r,int node){
    Tree[node].fg=true;
    if(l==r){
        Tree[node].sum=a[l];
        Tree[node].max=a[l];
        Tree[node].vl=a[l];
        Tree[node].vr=a[l];
        return ;
    }
    int mid=(l+r)>>1;
    build(l,mid,ls);build(mid+1,r,rs);
    updata(node);
}
void add(int l,int r,int node,int ps,int to){
    if(l>ps || r<ps)return ;
    if(l==r){
        Tree[node].sum=to;
        Tree[node].max=to;
        Tree[node].vl=to;
        Tree[node].vr=to;
        return ;
    }
    int mid=(l+r)>>1;
    add(l,mid,ls,ps,to);add(mid+1,r,rs,ps,to);
    updata(node);
}
Segtree query(int l,int r,int node,int sa,int se){
    if(sa<=l && r<=se)return Tree[node];
    int mid=(l+r)>>1;
    if(sa>mid)return query(mid+1,r,rs,sa,se);
    if(se<=mid)return query(l,mid,ls,sa,se);
    Segtree t,lson,rson;
    lson=query(l,mid,ls,sa,se);rson=query(mid+1,r,rs,sa,se);
    t.vl=max(lson.vl,lson.sum+rson.vl);t.vr=max(rson.vr,lson.vr+rson.sum);
    t.max=max(lson.vr+rson.vl,max(lson.max,rson.max));
    return t;
}
void work()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    build(1,n,1);
    int fg,x,y;
    while(m--){
        scanf("%d%d%d",&fg,&x,&y);
        if(fg==2)add(1,n,1,x,y);
        else printf("%d\n",query(1,n,1,x,y).max);
    }
}

namespace SOLVE {
    vector<int>pos[100010];
    void main(){
        REP(i,0,100010)pos[i].clear();
        int n,lim;
        in(n,lim);
        mst(a,0);
        build(1,n,1);
        int ans = 0;
        REP(i,1,n+1){
            int val;in(val);
            pos[val].PB(i);
            add(1, n, 1, i, 1);
//            change(1, i, 1);
            if(sz(pos[val]) > lim){
                add(1, n, 1, pos[val][sz(pos[val])-lim-1], -lim);
//                change(1, pos[val][sz(pos[val])-lim-1], -lim);
            }
            if(sz(pos[val]) > lim + 1){
                add(1, n, 1, pos[val][sz(pos[val])-lim-2], 0);
//                change(1, pos[val][sz(pos[val])-lim-2], 0);
            }
            upmax(ans, query(1,n,1,1,n).max);

        }
        cout<<ans<<endl;

    }
}


signed main() {
    int t;
    in(t);
//    t = 1;
    REP(i,1,t+1){
        cout<<"Case #"<<i<<": ";
        SOLVE::main();
    }
    return 0;
}
