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
  ll tot;
  int bsize;

  struct bucket{
    vector<int> vec;

    int gt(int val){
      int n = upper_bound(vec.begin() , vec.end() , val) - vec.begin();
      return vec.size() - n;
    }

    int ls(int val){
      int n = lower_bound(vec.begin() , vec.end() , val + 1) - vec.begin();
      return n;
    }

  }B[500];

  void build(){
    tot = 0;
    bsize = sqrt(N);
    for(int i = 0; i < N; ++i){
      bid[i] = i / bsize;
      B[bid[i]].vec.push_back(a[i]);
    }
    for(int i = 0; i <= bsize; ++i){
      sort(B[i].vec.begin() , B[i].vec.end());
    }
  }

  void update(int L , int R){
    if(a[L] > a[R])--tot;
    if(a[L] < a[R]) ++tot;
    int Lid = bid[L] , Rid = bid[R];
    int l = L % bsize , r = R % bsize;
    if(Lid == Rid){
      for(int i = L + 1; i < R; ++i){
        if(a[i] > a[L])++tot;
        if(a[i] < a[L])--tot;
        if(a[i] > a[R])--tot;
        if(a[i] < a[R])++tot;
      }
    }
    else {
      for(int i = Lid + 1; i < Rid; ++i){
        tot += B[i].gt(a[L]) - B[i].ls(a[L]);
        tot += -B[i].gt(a[R]) + B[i].ls(a[R]);
      }
      for(int i = l + 1; i < bsize; ++i){
        int aid = i + Lid * bsize;
        if(aid >= N)break;
        if(a[aid] > a[L])++tot;
        if(a[aid] < a[L])--tot;
        if(a[aid] > a[R])--tot;
        if(a[aid] < a[R])++tot;
      }
      for(int i = 0; i < r; ++i){
        int aid = i + Rid * bsize;
        if(aid >= N)break;
        if(a[aid] > a[L])++tot;
        if(a[aid] < a[L])--tot;
        if(a[aid] > a[R])--tot;
        if(a[aid] < a[R])++tot;
      }
      for(int i = 0; i < B[Lid].vec.size(); ++i){
        if(B[Lid].vec[i] == a[L])B[Lid].vec[i] = a[R];
      }
      sort(B[Lid].vec.begin() , B[Lid].vec.end());
      for(int i = 0; i < B[Rid].vec.size(); ++i){
        if(B[Rid].vec[i] == a[R])B[Rid].vec[i] = a[L];
      }
      sort(B[Rid].vec.begin() , B[Rid].vec.end());
    }
  }

  void show(){
    for(int i = 0; i <= bsize; ++i){
      cout << "for bucket = " << i << " : " << endl;
      for(int j : B[i].vec){
        cout << j << " ";
      }
      cout << endl;
    }
  }

} S;


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
    //S.show();
    S.update(l , r);
    printf("%lld\n" , S.tot);
    swap(a[l] , a[r]); // swap at the end
  }
}
