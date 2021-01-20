#include <bits/stdc++.h>
using namespace std;
vector<int> X;
vector<array<int , 2>> pt , tmp;
int N , M;

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        int l , r;
        scanf("%d %d" , &l , &r);
        tmp.push_back({l , r});
    }
    scanf("%d" , &M);
    for(int i = 1; i <= M; ++i){
        int x;
        scanf("%d" , &x);
        X.push_back(x);
    }
    for(array<int , 2>& e : tmp){
        int cnt = 0;
        for(int x : X){
            if(x <= e[1] && x >= e[0])++cnt;
        }
        if(cnt > 2){
            printf("impossible\n");
            return 0;
        }
        if(cnt < 2){
            pt.push_back(e);
        }
    }
    vector<int> ans;
    vector<int> XX;
    int j = -1;
    for(array<int , 2>& e : pt){
        while(j + 1 < X.size() && X[j + 1] <= e[1])XX.push_back(X[j + 1]) , ++j;
        vector<int> cover;
        for(int x : XX){
            if(x >= e[0])cover.push_back(x);
        }
        for(int x : ans){
            if(x >= e[0])cover.push_back(x);
        }
        if(cover.size() > 2){
            printf("impossible\n");
            return 0;
        }
        if(cover.size() == 2){
            continue;
        }
        if(cover.size() == 1){
            if(cover.back() == e[1])ans.push_back(e[1] - 1);
            else ans.push_back(e[1]);
        }
        if(cover.size() == 0){
            ans.push_back(e[1]);
            ans.push_back(e[1] - 1);
        }
    }   
    printf("%d\n" , (int)ans.size());
    for(int i : ans){
        printf("%d " , i);
    }
    printf("\n");
}