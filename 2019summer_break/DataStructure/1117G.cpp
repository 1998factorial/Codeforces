#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 1e6 + 10;
int N , Q;
int perm[maxn];
int ql[maxn];
int qr[maxn];
vector<int> id;
int L[maxn]; // L[i] = maximal j such that a[j] > a[i]
int R[maxn]; // R[i] = minimal j such that a[j] > a[i]


int main(){
  scanf("%d %d" , &N , &Q);
  for(int i = 1; i <= N; ++i){
    scanf("%d" , &perm[i]);
  }
  for(int i = 1; i <= Q; ++i){
    scanf("%d" , &ql[i]);
  }
  for(int i = 1; i <= Q; ++i){
    scanf("%d" , &qr[i]);
    id.push_back(i);
  }
  vector<int> stack;
  for(int i = 1; i <= N; ++i){
    while(!stack.empty() && perm[stack.back()] <= perm[i])stack.pop_back();
    if(!stack.empty())L[i] = stack.back();
    else L[i] = 0;
    stack.push_back(i);
  }
  stack.clear();
  for(int i = N; i >= 1; --i){
    while(!stack.empty() && perm[stack.back()] <= perm[i])stack.pop_back();
    if(!stack.empty())R[i] = stack.back();
    else R[i] = N + 1;
    stack.push_back(i);
  }

}
