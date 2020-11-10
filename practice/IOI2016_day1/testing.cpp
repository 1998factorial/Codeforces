#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline char nc(){
  static char buf[100000],*p1=buf,*p2=buf;
  if (p1==p2) { p2=(p1=buf)+fread(buf,1,100000,stdin); if (p1==p2) return EOF; }
  return *p1++;
}

inline void read(int &x){
  char c=nc(),b=1;
  for (;!(c>='0' && c<='9');c=nc()) if (c=='-') b=-1;
  for (x=0;c>='0' && c<='9';x=x*10+c-'0',c=nc()); x*=b;
}

const int N=400005;

int sx[N],icnt;

inline int Bin(int x){
  return lower_bound(sx+1,sx+icnt+1,x)-sx;
}

ll Ans=0;
int n,us[N],vs[N];
int c[N];

int fat[N];
inline int Fat(int u){
  return u==fat[u]?u:fat[u]=Fat(fat[u]);
}
inline bool Merge(int x,int y){
  x=Fat(x); y=Fat(y); if (x==y) return 0;
  fat[x]=y; return 1;
}

struct edge{
  int u,v,w;
  edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){ }
  bool operator < (const edge& B) const{
    return w<B.w;
  }
}edges[N];
int tot;

int main(){
  int t;
  //freopen("t.in","r",stdin);
  //freopen("t.out","w",stdout);
  cin >> n;
  for (int i=1;i<=n;i++) cin >> us[i] >> vs[i],sx[++icnt]=us[i],sx[++icnt]=vs[i];
  us[++n]=1<<30; vs[n]=1; sx[++icnt]=us[n],sx[++icnt]=vs[n];
  sort(sx+1,sx+icnt+1); icnt=unique(sx+1,sx+icnt+1)-sx-1;
  for (int i=1;i<=icnt;i++) fat[i]=i;//, printf("sx[%d] = %d\n" , i , sx[i]);
  for (int i=1;i<=n;i++){
    c[us[i]=Bin(us[i])]++,c[vs[i]=Bin(vs[i])]--,Merge(us[i],vs[i]);
  }
  for (int i=1;i<icnt;i++) c[i]+=c[i-1];// , printf("sum[%d] = %d\n" , i , c[i]);
  for (int i=1;i<icnt;i++){
    if (c[i]) Merge(i,i+1);
    if (c[i]>0){
      Ans+=(ll)c[i]*(sx[i+1]-sx[i]);
    }
  }
  for (int i=1;i<icnt;i++)
    if (Fat(i)!=Fat(i+1))
      edges[++tot]=edge(i,i+1,sx[i+1]-sx[i]);
  sort(edges+1,edges+tot+1);
  for (int i=1;i<=tot;i++)
    if (Merge(edges[i].u,edges[i].v))
      Ans+=edges[i].w;
  printf("%lld\n",Ans);
  return 0;
}
