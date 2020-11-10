/*
    Greedy + Data structure
    For each group, we are always trying to fit as many large size arrays in it
    So, it makes sense to think about what is the largest posisble size of array
    that I can put into my group now?
    With the help of multiset we can achieve this in NlogN time amortized
*/

#include <bits/stdc++.h>
#define MAXN 200005
using namespace std;

int N , K;
int C[MAXN];

int main(){
    scanf("%d %d" , &N , &K);
    multiset<int> s;
    for(int i = 1; i <= N; ++i){
        int x; scanf("%d" , &x); s.insert(x);
    }
    for(int i = 1; i <= K; ++i){
        scanf("%d" , &C[i]);
    }
    vector<int> cando;
    for(int i = K; i >= 1; --i){
        for(int x = 1; x <= C[i] - C[i + 1]; ++x){
            cando.push_back(i);
        }
    }
    vector<vector<int>> ret;
    while(!s.empty()){
        vector<int> group;
        for(int i : cando){
            auto it = s.lower_bound(i);
            if(it == s.end() || *it > i){
                if(it == s.begin())break;
                --it;
            }
            group.push_back(*it);
            s.erase(it);
        }
        ret.push_back(group);
    }
    printf("%d\n" , (int)ret.size());
    for(int i = 0; i < ret.size(); ++i){
        printf("%d " , (int)ret[i].size());
        for(int j : ret[i]){
            printf("%d " , j);
        }
        printf("\n");
    }
}
