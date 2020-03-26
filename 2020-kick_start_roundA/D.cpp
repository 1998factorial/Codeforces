#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

const int maxn = 1e6 + 10;
int N , K , tot , root;

int trie[maxn][26];
int cnt[maxn * 26];
int depth[maxn * 26];
int DP[maxn * 26];
int rem[maxn * 26];
int cnt2[maxn * 26];

int newT(){
  return ++tot;
}

void addTrie(string& s){
  int len = s.size();
  int v = root;
  for(int i = 0; i < len; ++i){
    int c = s[i] - 'A';
    if(trie[v][c] == 0)
      trie[v][c] = newT();
    v = trie[v][c];
    ++cnt[v];
    depth[v] = i + 1;
  }
}

void DFS(int v){
  bool isleaf = 1;
  int tot_used = 0;
  int tot_rem = 0;
  cnt2[v] = cnt[v];
  for(int i = 0; i < 26; ++i){
    if(trie[v][i]){
      isleaf = 0;
      int c = trie[v][i];
      DFS(c);
      DP[v] += DP[c];
      cnt2[v] -= cnt[c];
      tot_rem += rem[c];
    }
  }
  if(isleaf){
    DP[v] = depth[v] * (cnt[v] / K);
    rem[v] = cnt[v] % K;
  }
  else{
    int num = cnt2[v] + tot_rem;
    DP[v] += depth[v] * (num / K);
    rem[v] = num % K;
  }
}

int solve(){
  memset(trie , 0 , sizeof(trie));
  memset(cnt , 0 , sizeof(cnt));
  memset(depth , 0 , sizeof(depth));
  memset(DP , 0 , sizeof(DP));
  memset(rem , 0 , sizeof(rem));
  memset(cnt2 , 0 , sizeof(cnt2));
  cin >> N >> K;
  tot = 0;
  root = newT();
  for(int i = 1; i <= N; ++i){
    string s; cin >> s;
    addTrie(s);
  }
  DFS(root);
  return DP[root];
}


int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t; cin >> t;
  for(int x = 1; x <= t; ++x){
    cout << "Case #" << x << ": " << solve() << endl;
  }
}
