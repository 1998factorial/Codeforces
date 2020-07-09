#include <bits/stdc++.h>
#define ID 0
using namespace std;
typedef long long ll;

const int maxn = 5e5 + 10;
const int maxm = 1e7 + 10;

int a[maxn];
int p1[maxm] , p[maxm];
int N;
vector<pair<int , int>> ans;

void init(){
    p1[1] = 1;
    for(int i = 1; i < maxm; ++i)p[i] = 1;
    for(ll i = 2; i < maxm; ++i){
        if(!p1[i]){
            p1[i] = i;
            p[i] *= i;
            for(ll j = 2 * i; j < maxm; j += i){
                p1[j] = i;
                p[j] *= i;
            }
        }
    }
    if(ID)for(int i = 1; i <= 100; ++i){
        printf("p[%d] = %d , p1[%d] = %d\n" , i , p[i] , i , p1[i]);
    }
}


int main(){
    init();
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &a[i]);
        if(p1[a[i]] == p[a[i]]){
            ans.emplace_back(-1 , -1);
        }
        else{
            ans.emplace_back(p1[a[i]] , p[a[i]] / p1[a[i]]);
        }
    }
    for(auto& e : ans){
        printf("%d " , e.first);
    }
    printf("\n");
    for(auto& e : ans){
        printf("%d " , e.second);
    }
    printf("\n");
}
