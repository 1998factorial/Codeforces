/*
    Constructive
    instead of filling numbers, we can obatin an ordering of the vertices and assign them values
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int , int> ii;

int N;
vector<int> s[2005];
vector<int> g[2005];
int cnt[2005];
int ans[2005];
int isOK;

void DFS(int v , int p){
    if(!isOK)return;
    for(int u : g[v]){
        if(u != p){
            DFS(u , p);
            for(int i : s[u]){
                s[v].push_back(i);
            }
        }
    }
    if(cnt[v] > s[v].size()){
        isOK = 0;
    }
    else{
        s[v].insert(s[v].begin() + cnt[v] , v);
    }
}

int main(){
    isOK = 1;
    cin >> N;
    int root = 1;
    for(int i = 1; i <= N; ++i){
        int x , c; cin >> x >> cnt[i];
        if(x == 0){
            root = i;
        }
        else{
            g[x].push_back(i);
        }
    }
    DFS(root , -1);
    if(isOK){
        cout << "YES" << endl;
        for(int i = 0; i < N; ++i){
            int x = s[root][i];
            ans[x] = i + 1;
        }
        for(int i = 1; i <= N; ++i)cout << ans[i] << " ";
        cout << endl;
    }
    else{
        cout << "NO" << endl;
    }
}
