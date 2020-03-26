#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 1e5 + 10;
const int inf = 1e8 + 10;
int cheese[maxn];
int mice[maxn];
int N , M , Y0 , Y1;
unordered_map<int , int > mp;
vector<int> t;
int R[maxn];
int L[maxn];
int ans[maxn];

int main(){
  scanf("%d %d %d %d" , &N , &M , &Y0 , &Y1);
  for(int i = 1; i <= N; ++i){
    scanf("%d" , &mice[i]);
  }
  for(int i = 1; i <= M; ++i){
    scanf("%d" , &cheese[i]);
    mp[cheese[i]] = i;
    t.push_back(cheese[i]);
    ans[i] = inf;
  }
  for(int i = 1; i <= N; ++i){
    auto it = lower_bound(t.begin() , t.end() , mice[i]);
    if(it != t.end())R[i] = *it;
    else R[i] = inf;
  }
  for(int i = 0; i < M; ++i){
    t[i] *= -1;
  }
  reverse(t.begin() , t.end());
  for(int i = 1; i <= N; ++i){
    mice[i] *= -1;
  }
  for(int i = 1; i <= N; ++i){
    auto it = lower_bound(t.begin() , t.end() , mice[i]);
    if(it != t.end())L[i] = *it * (-1);
    else L[i] = -inf;
  }
  for(int i = 0; i < M; ++i){
    t[i] *= -1;
  }
  for(int i = 1; i <= N; ++i){
    mice[i] *= -1;
  }
  int ret = 0;
  for(int i = 1; i <= N; ++i){
    //printf("L[%d] = %d , R[%d] = %d\n" , i , L[i] , i , R[i]);
    int distance_l = abs(mice[i] - L[i]);
    int distance_r = abs(mice[i] - R[i]);

    if(distance_l < distance_r){
      int pos = mp[L[i]];
      int distance = abs(mice[i] - L[i]);
      if(ans[pos] >= inf){
        ans[pos] = distance;
        ++ret;
      }
      else{
        if(ans[pos] == distance){
          ++ret;
        }
        else if(ans[pos] > distance){
          ans[pos] = distance;
        }
      }
    }
    else if(distance_r < distance_l){
      int pos = mp[R[i]];
      int distance = abs(mice[i] - R[i]);
      if(ans[pos] >= inf){
        ans[pos] = distance;
        ++ret;
      }
      else{
        if(ans[pos] == distance){
          ++ret;
        }
        else if(ans[pos] > distance){
          ans[pos] = distance;
        }
      }
    }
    else{
      int pos_l = mp[L[i]];
      int pos_r = mp[R[i]];
      if(ans[pos_l] >= inf){ // L[i] is not taken
        ++ret;
        ans[pos_l] = distance_l;
        continue;
      }
      if(ans[pos_l] == distance_l){
        ++ret;
        continue;
      }
      if(ans[pos_r] >= inf){
        ++ret;
        ans[pos_r] = distance_r;
        continue;
      }
      if(ans[pos_r] > distance_r)ans[pos_r] = distance_r;
    }
  }
  printf("%d\n" , N - ret);
}
