#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<ll , ll> ii;
typedef unsigned long long ull;

const int maxn = 20;
int N , H;
int A[maxn] , B[maxn];
vector<ii> part1 , part2;
int tot;
ll sum[336196];

/*
  meet in the middle , divide into N / 2 and N / 2
  so we have 2 vectors of (x , y)
  sort 2 vectors and discrete y's
  reverse the second vector so we can do the following offline query:
  how many (x , y) in part2 such that my current x + x >= H and my current y + y >= H
  for the x direction, we can use 2 pointers to handle, the y direction can be
  handled by using data structure that supports point updates and range querys
  Fenwick tree can do the job
  time Complexity : O(3 ^ (N / 2) * log(3 ^ (N / 2)))
*/


void add(int pos , int val){
  while(pos <= tot){
    sum[pos] += val;
    pos += pos & (-pos);
  }
}

ll ask(int pos){
  ll ret = 0;
  while(pos){
    ret += sum[pos];
    pos -= pos & (-pos);
  }
  return ret;
}


ll solve(){
  memset(sum , 0 , sizeof(sum));
  part1.clear();
  part2.clear();
  int sz1 = ceil((double)N / 2);
  int sz2 = N - sz1;
  // compute part1 first
  int up = 1;
  for(int i = 1; i <= sz1; ++i)up *= 3;
  for(ll s = 0; s < up; ++s){
    ll x1 = 0 , y1 = 0;
    vector<int> mask;
    ll n = s;
    // compute mask
    while(n){
      mask.push_back(n % 3);
      n /= 3ll;
    }
    for(int i = mask.size(); i < sz1; ++i){
      mask.push_back(0);
    }
    for(int i = 0; i < sz1; ++i){
      if(mask[i] == 0){
        x1 += A[i];
      }
      if(mask[i] == 1){
        y1 += B[i];
      }
      if(mask[i] == 2){
        x1 += A[i];
        y1 += B[i];
      }
    }
    part1.emplace_back(x1 , y1);
  }

  // compute part 2
  up = 1;
  for(int i = 1; i <= sz2; ++i)up *= 3;
  for(ll s = 0; s < up; ++s){
    ll x1 = 0 , y1 = 0;
    vector<int> mask;
    ll n = s;
    // compute mask
    while(n){
      mask.push_back(n % 3);
      n /= 3ll;
    }
    for(int i = mask.size(); i < sz2; ++i){
      mask.push_back(0);
    }
    for(int i = sz1; i < N; ++i){
      if(mask[i - sz1] == 0){
        x1 += A[i];
      }
      if(mask[i - sz1] == 1){
        y1 += B[i];
      }
      if(mask[i - sz1] == 2){
        x1 += A[i];
        y1 += B[i];
      }
    }
    part2.emplace_back(x1 , y1);
  }
  sort(part1.begin() , part1.end());
  sort(part2.begin() , part2.end());
  reverse(part2.begin() , part2.end());
  vector<ll> tmp;
  for(auto& e : part1){
    tmp.push_back(e.second);
    tmp.push_back(H - e.second);
    tmp.push_back(H - e.second + 1);
    tmp.push_back(H - e.second - 1);
  }
  for(auto& e : part2){
    tmp.push_back(e.second);
    tmp.push_back(H - e.second);
    tmp.push_back(H - e.second + 1);
    tmp.push_back(H - e.second - 1);
  }
  sort(tmp.begin() , tmp.end());
  unordered_map<ll , ll> mp , imp;
  tot = 1;
  for(ll i : tmp){
    if(mp[i] == 0){
      mp[i] = tot;
      imp[tot] = i;
      ++tot;
    }
  }
  ll ret = 0;
  int i = 0 , j = 0;
  for(; i < part1.size(); ++i){
    while(j < part2.size() && part2[j].first >= H - part1[i].first){
      add(mp[part2[j].second] , 1);
      ++j;
    }
    ll val = ask(tot) - ask(mp[H - part1[i].second - 1]);
    ret += val;
  }
  return ret;
}

int main(){
  int T; scanf("%d" , &T);
  for(int t = 1; t <= T; ++t){
    scanf("%d %d" , &N , &H);
    for(int i = 0; i < N; ++i){
      scanf("%d" , &A[i]);
    }
    for(int i = 0; i < N; ++i){
      scanf("%d" , &B[i]);
    }
    printf("Case #%d: %lld\n" , t , solve());
  }
}
