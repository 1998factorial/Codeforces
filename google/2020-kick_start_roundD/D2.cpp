#include <bits/stdc++.h>
using namespace std;
template<typename T1,typename T2> inline void chmin(T1 &a,T2 b){if(a>b) a=b;}
template<typename T1,typename T2> inline void chmax(T1 &a,T2 b){if(a<b) a=b;}
using Int = long long;
const char newl = '\n';


struct UnionFind{
  Int num;
  vector<Int> rs,ps;
  UnionFind(){}
  UnionFind(Int n):num(n),rs(n,1),ps(n,0){iota(ps.begin(),ps.end(),0);}
  Int find(Int x){
    return (x==ps[x]?x:ps[x]=find(ps[x]));
  }
  bool same(Int x,Int y){
    return find(x)==find(y);
  }
  void unite(Int x,Int y){
    x=find(x);y=find(y);
    if(x==y) return;
    if(rs[x]<rs[y]) swap(x,y);
    rs[x]+=rs[y];
    ps[y]=x;
    num--;
  }
  Int size(Int x){
    return rs[find(x)];
  }
  Int count() const{
    return num;
  }
};

//INSERT ABOVE HERE
signed solve(){
  Int n,q;
  cin>>n>>q;
  vector<Int> ds(n-1);
  for(Int i=0;i<n-1;i++) cin>>ds[i];

  vector<Int> ss(q),ks(q);
  for(Int i=0;i<q;i++) cin>>ss[i]>>ks[i],ss[i]--;

  using P = pair<Int, Int>;
  vector<P> vp;
  for(Int i=0;i<n-1;i++)
    vp.emplace_back(ds[i],i);
  sort(vp.begin(),vp.end());

  vector<Int> ord(n-1);
  for(Int i=0;i<n-1;i++)
    ord[i]=vp[i].second;

  // check(ls[i]) = false
  // check(rs[i]) = true
  vector<Int> ls(q,-1),rs(q,n-1);
  while(1){
    Int flg=0;
    vector<vector<Int>> G(n);
    for(Int i=0;i<q;i++){
      if(ls[i]+1<rs[i]){
        Int mid=(ls[i]+rs[i])>>1;
        G[mid].emplace_back(i);
        flg=1;
      }
    }
    if(!flg) break;
    UnionFind uf(n);
    for(Int i=0;i<n-1;i++){
      uf.unite(ord[i],ord[i]+1);
      for(Int k:G[i]){
        if(uf.size(ss[k])>=ks[k]) rs[k]=i;
        else ls[k]=i;
      }
    }
  }

  vector<Int> ans(q);
  vector<vector<Int>> G(n+1);
  for(Int i=0;i<q;i++){
    assert(rs[i]<n-1);
    if(ks[i]==1){
      ans[i]=ss[i];
    }else{
      G[rs[i]].emplace_back(i);
    }
  }

  UnionFind uf(n);
  for(Int i=0;i<n-1;i++){
    // [xL, xR] [yL, yR]
    Int xR=ord[i];
    Int xL=xR-(uf.size(xR)-1);
    assert(uf.same(xL,xR));

    Int yL=ord[i]+1;
    Int yR=yL+(uf.size(yL)-1);
    assert(uf.same(yL,yR));

    for(Int k:G[i]){
      assert(uf.size(ss[k])<ks[k]);
      if(uf.same(xL,ss[k])){
        ans[k]=yL+(ks[k]-(uf.size(ss[k])+1));
      }else{
        ans[k]=xR-(ks[k]-(uf.size(ss[k])+1));
      }
    }
    uf.unite(ord[i],ord[i]+1);
  }

  for(Int i=0;i<q;i++) cout<<' '<<ans[i]+1;
  cout<<newl;
  return 0;
}

signed main(){
  cin.tie(0);
  ios::sync_with_stdio(0);
  Int T;
  cin>>T;
  for(Int t=1;t<=T;t++){
    cout<<"Case #"<<t<<":";
    solve();
  }

  return 0;
}
