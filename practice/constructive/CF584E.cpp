/*
    Constructive
    cost to swap p[i] and p[j] is abs(i - j), we need to find the minimal cost to transform p into t
*/
#include <bits/stdc++.h>
using namespace std;
int N;
int p[2005] , s[2005] , t[2005];
int main(){
    int cost = 0;
    vector<pair<int , int>> ops;
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i)scanf("%d" , &p[i]);
    for(int i = 1; i <= N; ++i)scanf("%d" , &s[i]) , t[s[i]] = i;
    for(int i = 1; i <= N; ++i){
        if(p[i] == s[i])continue;
        int pos = -1;
        for(int j = i + 1; j <= N; ++j){
            if(p[j] == s[i]){
                pos = j;
                break;
            }
        }
        for(int j = pos - 1; j >= i; --j){
            if(t[p[j]] < pos)continue;
            swap(p[j] , p[pos]);
            cost += pos - j;
            ops.emplace_back(pos , j);
            pos = j;
        }
    }
    printf("%d\n%d\n" , cost , (int)ops.size());
    for(auto& e : ops)printf("%d %d\n" , e.first , e.second);
}
