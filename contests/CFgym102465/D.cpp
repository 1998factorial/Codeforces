#include <bits/stdc++.h>
using namespace std;
const int maxn = 100005;
int cnt[maxn];
vector<int> pt[maxn];
int X , Y , N;

int main(){
    scanf("%d %d" , &X , &Y);
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        int x , y;
        scanf("%d %d" , &x , &y);
        pt[x].push_back(y);
    }
    for(int i = 0; i < X; ++i){
        sort(pt[i].begin() , pt[i].end());
        for(int j = 0; j < pt[i].size(); ++j){
            if(j - 1 >= 0 && pt[i][j] == pt[i][j - 1])continue;
            ++cnt[pt[i][j]];
        }
    }
    int ans = Y;
    int v = 0 , nup = 0 , ndown = 0;
    for(int i = X - 1; i >= 0; --i){
        v += ndown;
        ndown += cnt[i];
    }
    printf("nup = %d , ndown = %d , v = %d\n" , nup , ndown , v);
    int minv = v;
    for(int i = 0; i < X - 1; ++i){
        printf("at i = %d\n" , i);
        nup += cnt[i];
        ndown -= cnt[i];
        v += nup;
        v -= ndown;
        minv = min(minv , v);
        printf("nup = %d , ndown = %d , v = %d\n" , nup , ndown , v);
    }
    printf("minv = %d\n" , minv);
    ans += minv * 2;
    printf("%d\n" , ans);
}