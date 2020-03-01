#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;
/*
  use sqrt decomp to solve this problem
  each bucket has cnt[10000] and delta
*/
const int maxn = 1e5 + 10;
vector<int> lucky;
bool islucky[10005];
int N , M;
int a[maxn];
int bucketid[maxn];

struct sqrtDecomp{
  int bucket_size;

  struct bucket{
    int cnt[10005];
    int delta;
  } buckets[355];

  void build(){
    bucket_size = sqrt(N);
    for(int i = 0; i < N; ++i){
      bucketid[i] = i / bucket_size;
      ++buckets[bucketid[i]].cnt[a[i]];
    }
  }

  void update(int L , int R , int d){
    int BL = bucketid[L] , BR = bucketid[R];
    int l = L % bucket_size , r = R % bucket_size;
    for(int i = BL + 1; i < BR; ++i){
      buckets[i].delta += d;
    }
    if(BL == BR){
      // update buckets[BL]
      for(int i = 0; i < bucket_size; ++i){
        int x = bucket_size * BL + i;
        if(x >= N)break;
        buckets[BL].cnt[a[x]] = 0;
        a[x] += buckets[BL].delta;
      }
      for(int i = 0; i < bucket_size; ++i){
        int x = bucket_size * BL + i;
        if(x >= N)break;
        if(L <= x && x <= R)a[x] += d;
        ++buckets[BL].cnt[a[x]];
      }
    }
    else{
      // update buckets[BL]
      for(int i = 0; i < bucket_size; ++i){
        int x = bucket_size * BL + i;
        if(x >= N)break;
        buckets[BL].cnt[a[x]] = 0;
        a[x] += buckets[BL].delta;
      }
      for(int i = 0; i < bucket_size; ++i){
        int x = bucket_size * BL + i;
        if(L <= x)a[x] += d;
        ++buckets[BL].cnt[a[x]];
      }
      // update buckets[BR]
      for(int i = 0; i < bucket_size; ++i){
        int x = bucket_size * BR + i;
        if(x >= N)break;
        buckets[BR].cnt[a[x]] = 0;
        a[x] += buckets[BR].delta;
      }
      for(int i = 0; i < bucket_size; ++i){
        int x = bucket_size * BR + i;
        if(x >= N)break;
        if(x <= R)a[x] += d;
        ++buckets[BR].cnt[a[x]];
      }
    }
    buckets[BL].delta = buckets[BR].delta = 0;
  }

  int query(int L , int R){
    int BL = bucketid[L] , BR = bucketid[R];
    int l = L % bucket_size , r = R % bucket_size;
    int ret = 0;
    for(int i = BL + 1; i < BR; ++i){
      for(int j : lucky){
        if(j - buckets[i].delta >= 0){
          ret += buckets[i].cnt[j - buckets[i].delta];
        }
      }
    }
    if(BL == BR){
      for(int i = 0; i < bucket_size; ++i){
        int x = bucket_size * BL + i;
        if(x >= N)break;
        if(L <= x && x <= R){
          ret += islucky[a[x] + buckets[BL].delta];
        }
      }
    }
    else{
      for(int i = 0; i < bucket_size; ++i){
        int x = bucket_size * BL + i;
        if(x >= N)break;
        if(L <= x){
          ret += islucky[a[x] + buckets[BL].delta];
        }
      }
      for(int i = 0; i < bucket_size; ++i){
        int x = bucket_size * BR + i;
        if(x >= N)break;
        if(x <= R){
          ret += islucky[a[x] + buckets[BR].delta];
        }
      }
    }
    return ret;
  }

} S;

int main(){
  lucky.push_back(4); lucky.push_back(7);
  lucky.push_back(44); lucky.push_back(47);
  lucky.push_back(74); lucky.push_back(77);
  lucky.push_back(444); lucky.push_back(447);
  lucky.push_back(474); lucky.push_back(477);
  lucky.push_back(744); lucky.push_back(747);
  lucky.push_back(774); lucky.push_back(777);
  lucky.push_back(4444); lucky.push_back(4447);
  lucky.push_back(4474); lucky.push_back(4477);
  lucky.push_back(4744); lucky.push_back(4747);
  lucky.push_back(4774); lucky.push_back(4777);
  lucky.push_back(7444); lucky.push_back(7447);
  lucky.push_back(7474); lucky.push_back(7477);
  lucky.push_back(7744); lucky.push_back(7747);
  lucky.push_back(7774); lucky.push_back(7777);
  for(int i : lucky)islucky[i] = 1;
  scanf("%d %d" , &N , &M);
  for(int i = 0; i < N; ++i){
    scanf("%d" , &a[i]);
  }
  S.build();
  for(int q = 1; q <= M; ++q){
    char p[10];
    int l , r;
    scanf("%s %d %d" , p , &l , &r);
    --l , --r;
    if(p[0] == 'c'){
      printf("%d\n" , S.query(l , r));
    }
    else{
      int d; scanf("%d" , &d);
      if(d == 0)continue;
      S.update(l , r , d);
    }
  }
}
