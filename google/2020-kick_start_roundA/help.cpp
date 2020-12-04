#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
const int alpha = 26;
bool canwin[maxn];
bool canlose[maxn];
int trie[maxn][alpha];
int tot , root , N , K;

int newT(){
  return ++tot;
}

void addTrie(string& s){ // process a new string , add it into trie
  int len = s.size();
  int v = root;
  for(int i = 0; i < len; ++i){
    int c = s[i] - 'a';
    if(trie[v][c] == 0)trie[v][c] = newT();
    v = trie[v][c];
  }
}

void DFS(int v){
  bool isleaf = 1;
  canwin[v] = 0;
  canlose[v] = 0;
  for(int i = 0; i < alpha; ++i){
    if(trie[v][i]){
      isleaf = 0;
      int to = trie[v][i];
      DFS(to);
      canwin[v] |= !canwin[to];
      canlose[v] |= !canlose[to];
    }
  }
  if(isleaf){
    canwin[v] = 0;
    canlose[v] = 1;
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N >> K;
  tot = 0;
  root = newT();
  for(int i = 1; i <= N; ++i){
    string s; cin >> s;
    addTrie(s);
  }
  DFS(root);
  if((canwin[root] && canlose[root]) || (canwin[root] && K % 2
  ))cout << "First" << endl;
  else cout << "Second" << endl;
}
