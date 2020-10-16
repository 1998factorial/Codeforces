#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 10;
int N;

vector<int> query(int pos , int bit , set<int>& vis){
    vector<int> qs , ret(N + 1 , INF);
    for(int i = 1; i <= N; ++i){
        int v = (i & (1 << pos)) != 0;
        if(v == bit){
            qs.push_back(i);
            vis.insert(i);
        }
    }
    if((int)qs.size() == 0)return ret;
    printf("%d\n" , (int)qs.size());
    for(int i = 0; i < (int)qs.size(); ++i){
        printf("%d " , qs[i]);
    }
    printf("\n");
    fflush(stdout);
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &ret[i]);
    }
    return ret;
}

void interact(vector<int>& ans){
    for(int i = 0; i < 10; ++i){
        for(int j : {0 , 1}){
            set<int> vis;
            vector<int> ret = query(i , j , vis);
            for(int k = 1; k <= N; ++k){
                if(!vis.count(k)){ // not querying diagonal element
                    ans[k] = min(ans[k] , ret[k]);
                }
            }
        }
    }
}

int main(){
    scanf("%d" , &N);
    vector<int> ans(N + 1 , INF);
    interact(ans);
    printf("-1\n");
    for(int i = 1; i <= N; ++i){  
        printf("%d " , ans[i]);
    }
    printf("\n");
    fflush(stdout);
}