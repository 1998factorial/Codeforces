#include <bits/stdc++.h>
using namespace std;

int main(){
    int sz , K; scanf("%d %d" , &sz , &K);
    vector<int> a;
    for(int i = 1; i <= sz; ++i){
        int x; scanf("%d" , &x);
        a.push_back(x);
    }
    sort(a.begin() , a.end());
    vector<int> q;
    for(int i = 0; i < sz; ++i){
        while(!q.empty() && a[i] - K <= q.back() && a[i] > q.back())q.pop_back();
        q.push_back(a[i]);
    }
    printf("%d\n" , (int)q.size());
}
