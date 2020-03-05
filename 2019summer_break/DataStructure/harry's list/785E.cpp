#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 2e5 + 10;
int N , Q;
int a[maxn];
int bid[maxn];

struct sqrtdecomp{
  int bucket_size;
  ll tot;
  struct bucket{
    int sum[maxn << 1];

    void add(int pos , int val){
      while(pos <= N){
        sum[pos] += val;
        pos += pos & (-pos);
      }
    }

    int ask(int pos){
      int ret = 0;
      while(pos){
        ret += sum[pos];
        pos -= pos & (-pos);
      }
      return ret;
    }

  }B[450];

  void build(){
    bucket_size = sqrt(N);
    tot = 0;
    for(int i = 0; i < N; ++i){
      bid[i] = i / bucket_size;
      B[bid[i]].add(a[i] , 1);
    }
  }

  void update(int start , int end){
    if(a[start] > a[end])--tot;
    if(a[start] < a[end]) ++tot;
    int L = bid[start] , R = bid[end];
    int l = start % bucket_size , r = end % bucket_size;
    if(L == R){
      for(int i = start + 1; i < end; ++i){
        if(a[i] > a[start])++tot;
        if(a[i] < a[start])--tot;
        if(a[i] > a[end])--tot;
        if(a[i] < a[end])++tot;
      }
    }
    else{
      for(int i = L + 1; i < R; ++i){
        tot += (B[i].ask(N) - B[i].ask(a[start])) - B[i].ask(a[start] - 1);
        tot += -(B[i].ask(N) - B[i].ask(a[end])) + B[i].ask(a[end] - 1);
      }
      for(int i = l + 1; i < bucket_size; ++i){
        //DEBUG(i);
        int aid = i + L * bucket_size;
        //DEBUG(a[aid]);
        //DEBUG(aid);
        if(aid >= N)break;
        if(a[aid] > a[start])++tot;
        if(a[aid] < a[start])--tot;
        if(a[aid] > a[end])--tot;
        if(a[aid] < a[end])++tot;
      }
      for(int i = 0; i < r; ++i){
        //DEBUG(i);
        int aid = i + R * bucket_size;
        //DEBUG(a[aid]);
        //DEBUG(aid);
        if(aid >= N)break;
        if(a[aid] > a[start])++tot;
        if(a[aid] < a[start])--tot;
        if(a[aid] > a[end])--tot;
        if(a[aid] < a[end])++tot;
      }
      B[L].add(a[start] , -1);
      B[L].add(a[end] , 1);
      B[R].add(a[end] , -1);
      B[R].add(a[start] , 1);
    }
  }

  void show(){
    for(int i = 0; i < N; ++i)
      printf("bid[%d] = %d\n" , i , bid[i]);
  }

}S;


int main(){
  scanf("%d %d" , &N , &Q);
  for(int i = 0; i < N; ++i)a[i] = i + 1;
  S.build();
  //S.show();
  for(int q = 1; q <= Q; ++q){
    int l , r;
    scanf("%d %d" , &l , &r);
    --l , --r;
    if(l > r)swap(l , r);
    S.update(l , r);
    printf("%lld\n" , S.tot);
    swap(a[l] , a[r]); // swap at the end
  }
}
