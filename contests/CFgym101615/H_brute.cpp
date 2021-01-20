#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
const int INF = 1e9 + 10;
const int maxn = 2e5 + 10;
int N , M;
struct flight{
    int v , nv , s , e;
    flight(){}
    flight(int v_ , int nv_ , int s_ , int e_) : v(v_) , nv(nv_) , s(s_) , e(e_) {}
    bool operator < (const flight& rhs) const {
        return e < rhs.e;
    }
};
flight f[maxn];
int DP[maxn];

int main(){
    scanf("%d %d" , &N , &M);
    for(int i = 1; i <= M; ++i){
        scanf("%d %d %d %d" , &f[i].v , &f[i].nv , &f[i].s , &f[i].e);
    }
    f[++M] = flight(1 , 1 , 0 , 0);
    sort(f + 1 , f + 1 + M);
    for(int i = 1; i <= M; ++i)DP[i] = INF;
    DP[1] = 0;
    ID for(int i = 1; i <= M; ++i){
        printf("(%d %d %d %d)\n" , f[i].v , f[i].nv , f[i].s , f[i].e);
    }
    for(int i = 2; i <= M; ++i){
        for(int j = 1; j < i; ++j){
            if(f[j].nv == f[i].v && f[j].e <= f[i].s){
                DP[i] = min(DP[i] , DP[j] + (f[i].s - f[j].e) * (f[i].s - f[j].e));
            }
        }
        ID printf("DP[%d] = %d\n" , i , DP[i]);
    }   
    int ret = INF;
    for(int i = 1; i <= M; ++i){
        if(f[i].nv == N){
            ret = min(ret , DP[i]);
        }
    }
    printf("%d\n" , ret);
}