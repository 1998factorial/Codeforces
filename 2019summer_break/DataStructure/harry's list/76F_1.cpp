#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;
const int maxn = 1e5 + 10;
/*
  an event i can reach event j iff |xi - xj| <= V * (tj - ti)
  O(N * N) solution comes to me instantly
  sort the events by time
  dp[i] = "the maximal number of events we can visit for the first i happened events , given that
  we are going to end up at event[i]"
  dp[i] = max{dp[j] | j < i & eve[j] can reach eve[i]} + 1
*/
struct event{
  int x , t;
  event(){}
  event(int a , int b) : x(a) , t(b){}
  bool operator < (const event& rhs) const {
    return t < rhs.t;
  }
} eve[maxn];

int dp[maxn];
int N , V;

int main(){
  scanf("%d" , &N);
  for(int i = 1; i <= N; ++i){
    scanf("%d %d" , &eve[i].x , &eve[i].t);
  }
  scanf("%d" , &V);
  sort(eve + 1 , eve + 1 + N);
  int ans2 = 0;
  for(int i = 1; i <= N; ++i){
    dp[i] = 1;
    for(int j = i - 1; j >= 1; --j){
      if(abs(eve[i].x - eve[j].x) <= V * (eve[i].t - eve[j].t)){
        dp[i] = max(dp[i] , dp[j] + 1);
      }
    }
    ans2 = max(ans2 , dp[i]);
  }
  eve[++N].x = 0 , eve[N].t = 0;
  sort(eve + 1 , eve + 1 + N);
  int ans1 = 0;
  for(int i = 1; i <= N; ++i)dp[i] = -N;
  dp[1] = 0;
  for(int i = 2; i <= N; ++i){
    cout << eve[i].x << " " << eve[i].t << endl;
    for(int j = i - 1; j >= 1; --j){
      if(abs(eve[i].x - eve[j].x) <= V * (eve[i].t - eve[j].t)){
        //printf("eve[%d] -> eve[%d]\n" , j , i);
        dp[i] = max(dp[i] , dp[j] + 1);
      }
    }
    printf("dp[%d] = %d\n" , i , dp[i]);
    ans1 = max(ans1 , dp[i]);
  }
  printf("%d %d\n" , ans1 , ans2);
}
