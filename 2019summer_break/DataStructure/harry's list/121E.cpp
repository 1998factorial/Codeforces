#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 1e5 + 10;
int N , M;
bool Bnum[maxn];
int a[maxn];
int tree[maxn << 2];

void add(int pos , int val){
  while(pos <= N){
    tree[pos] += val;
    pos += pos & (-pos);
  }
}

int ask(int pos){
  int ret = 0;
  while(pos){
    ret += tree[pos];
    pos -= pos & (-pos);
  }
  return ret;
}

int main(){
  scanf("%d %d" , &N , &M);
  Bnum[4] = Bnum[7] = 1;
  Bnum[47] = Bnum[44] = Bnum[74] = Bnum[77] = 1;
  Bnum[444] = Bnum[474] = Bnum[477] = Bnum[447] = 1;
  Bnum[744] = Bnum[774] = Bnum[777] = Bnum[747] = 1;
  Bnum[4444] = Bnum[4474] = Bnum[4477] = Bnum[4447] = 1;
  Bnum[4744] = Bnum[4774] = Bnum[4777] = Bnum[4747] = 1;
  Bnum[7444] = Bnum[7474] = Bnum[7477] = Bnum[7447] = 1;
  Bnum[7744] = Bnum[7774] = Bnum[7777] = Bnum[7747] = 1;
  for(int i = 1; i <= N; ++i){
    scanf("%d" , &a[i]);
    if(Bnum[a[i]]){
      add(i , 1);
    }
  }
  for(int i = 1; i <= M; ++i){
    char p[10];
    scanf("%s" , p);
    if(p[0] == 'c'){
      int l , r;
      scanf("%d %d" , &l , &r);
      printf("%d\n" , ask(r) - ask(l - 1));
    }
    else{
      int l , r , v;
      scanf("%d %d %d" , &l , &r , &v);
      if(v == 0)continue;
      for(int j = l; j <= r; ++j){
        if(Bnum[a[j]]){
          add(j , -1);
        }
        a[j] += v;
        if(Bnum[a[j]]){
          add(j , 1);
        }
      }
    }
  }
}
