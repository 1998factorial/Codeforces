#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 1e6 + 10;
int N , a[maxn] , M;
int S[maxn];
int pre[maxn];
int tree[maxn << 1];
int ans[maxn];

struct query{
  int l , r , id;
  query(){}
  query(int a , int b , int c) : l(a) , r(b) , id(c) {}
  bool operator < (const query rhs) const {
    return r < rhs.r;
  }
}qs[maxn];
unordered_map<int , int> mp;

void add(int pos , int val){
  while(pos <= N){
    tree[pos] ^= val;
    pos += pos & (-pos);
  }
}

int ask(int pos){
  int ret = 0;
  while(pos){
    ret ^= tree[pos];
    pos -= pos & (-pos);
  }
  return ret;
}

int main(){
  scanf("%d" , &N);
  for(int i = 1; i <= N; ++i){
    scanf("%d" , &a[i]);
    S[i] = S[i - 1] ^ a[i];
    if(mp[a[i]] == 0){
      mp[a[i]] = i;
    }
    else{
      pre[i] = mp[a[i]];
      mp[a[i]] = i;
    }
  }
  cin >> M;
  for(int i = 1; i <= M; ++i){
    int l , r;
    scanf("%d %d" , &l , &r);
    qs[i] = query(l , r , i);
  }
  sort(qs + 1 , qs + 1 + M);
  int j = 1;
  for(int i = 1; i <= M; ++i){
    for(; j <= N && j <= qs[i].r; ++j){
      if(pre[j] > 0)
        add(pre[j] , a[j]);
      add(j , a[j]);
    }
    int ret = ask(qs[i].r) ^ ask(qs[i].l - 1);
    ans[qs[i].id] = ret ^ S[qs[i].l - 1] ^ S[qs[i].r];
  }
  for(int i = 1; i <= M; ++i){
    printf("%d\n" , ans[i]);
  }
}
