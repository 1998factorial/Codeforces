#include <bits/stdc++.h>
#define fi first
#define se second
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rrep(i,n) for(int i = 1; i <= (n); ++i)
#define drep(i,n) for(int i = (n)-1; i >= 0; --i)
#define srep(i,s,t) for (int i = s; i < t; ++i)
#define rng(a) a.begin(),a.end()
#define rrng(a) a.rbegin(),a.rend()
#define maxs(x,y) (x = max(x,y))
#define mins(x,y) (x = min(x,y))
#define limit(x,l,r) max(l,min(x,r))
#define lims(x,l,r) (x = max(l,min(x,r)))
#define isin(x,l,r) ((l) <= (x) && (x) < (r))
#define pb push_back
#define eb emplace_back
#define sz(x) (int)(x).size()
#define pcnt __builtin_popcountll
#define uni(x) x.erase(unique(rng(x)),x.end())
#define snuke srand((unsigned)clock()+(unsigned)time(NULL));
#define show(x) cout<<#x<<" = "<<x<<endl;
#define PQ(T) priority_queue<T,v(T),greater<T> >
#define bn(x) ((1<<x)-1)
#define dup(x,y) (((x)+(y)-1)/(y))
#define newline puts("")
#define v(T) vector<T>
#define vv(T) v(v(T))
using namespace std;
typedef long long ll;
typedef unsigned uint;
typedef unsigned long long ull;
typedef pair<int,int> P;
typedef tuple<int,int,int> T;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<P> vp;
typedef vector<T> vt;
inline int getInt() { int x; scanf("%d",&x); return x;}
template<typename T>inline istream& operator>>(istream&i,v(T)&v)
{rep(j,sz(v))i>>v[j];return i;}
template<typename T>string join(const v(T)&v)
{stringstream s;rep(i,sz(v))s<<' '<<v[i];return s.str().substr(1);}
template<typename T>inline ostream& operator<<(ostream&o,const v(T)&v)
{if(sz(v))o<<join(v);return o;}
template<typename T1,typename T2>inline istream& operator>>(istream&i,pair<T1,T2>&v)
{return i>>v.fi>>v.se;}
template<typename T1,typename T2>inline ostream& operator<<(ostream&o,const pair<T1,T2>&v)
{return o<<v.fi<<","<<v.se;}
template<typename T>inline ll suma(const v(T)& a) { ll res(0); for (auto&& x : a) res += x; return res;}
const double eps = 1e-10;
const ll LINF = 1001002003004005006ll;
const int INF = 1001001001;
#define dame { puts("IMPOSSIBLE"); return;}
#define yn {puts("YES");}else{puts("NO");}
const int MX = 200005;

// bipartite matching
struct match {
  vector<int> pre, root;
  vector<vector<int>> to;
  vector<int> p, q;
  int n, m;
  match(int n, int m):pre(n,-1),root(n,-1),to(n),p(n,-1),q(m,-1),n(n),m(m){}
  void add(int a, int b) { to[a].pb(b);}
  int solve() {
    int res = 0;
    bool upd = true;
    while (upd) {
      upd = false;
      queue<int> s;
      rep(i,n) if (!~p[i]) {
        root[i] = i;
        s.push(i);
      }
      while (sz(s)) {
        int v = s.front(); s.pop();
        if (~p[root[v]]) continue;
        rep(i,sz(to[v])) {
          int u = to[v][i];
          if (!~q[u]) {
            while (~u) {
              q[u] = v;
              swap(p[v],u);
              v = pre[v];
            }
            upd = true;
            ++res;
            break;
          }
          u = q[u];
          if (~pre[u]) continue;
          pre[u] = v; root[u] = root[v];
          s.push(u);
        }
      }
      if (upd) fill(rng(pre),-1), fill(rng(root),-1);
    }
    return res;
  }
};
//
struct Solver {
  void solve() {
    int n,k;
    scanf("%d%d",&n,&k);
    if (k < n || k > n*n) dame;
    vector<vector<int>> ans(n,vector<int>(n));
    if (k%n == 0) {
      rep(i,n) ans[i][i] = k/n;
    } else {
      if (k == n+1 || k == n*n-1) dame;
      if (n <= 3) dame;
      vector<int> a(n);
      rep(i,k) a[i%n]++;
      int r = k%n;
      bool three = true;
      if (r == 1) {
        a[1]++; a[n-1]--;
      } else if (r == n-1) {
        a[0]++; a[n-2]--;
        reverse(rng(a));
      } else {
        int x = a[0], y = a.back();
        rep(i,r) ans[i][(i+1)%r] = y;
        rep(i,(n-r)) ans[r+i][r+(i+1)%(n-r)] = x;
        three = false;
      }
      if (three) {
        int x = a[0], y = a[2], z = a.back();
        ans[0][1] = ans[1].back() = ans.back()[0] = y;
        rep(i,n-1) ans[(i+1)%(n-1)][i] = z;
        rep(i,n-2) ans[2+i][2+(i+1)%(n-2)] = x;
      }
      rep(i,n) ans[i][i] = a[i];
    }
    rrep(x,n) {
      int cnt = 0;
      rep(i,n)rep(j,n) if (ans[i][j] == x) ++cnt;
      if (cnt) {
        assert(cnt == n);
        continue;
      }
      match g(n,n);
      rep(i,n)rep(j,n) if (ans[i][j] == 0) g.add(i,j);
      g.solve();
      rep(i,n) ans[i][g.p[i]] = x;
    }
    cout<<"POSSIBLE"<<endl;
    rep(i,n) cout<<ans[i]<<endl;
  }
};

int main() {
  int ts;
  scanf("%d",&ts);
  rrep(ti,ts) {
    Solver solver;
    printf("Case #%d: ",ti);
    solver.solve();
  }
  return 0;
}
