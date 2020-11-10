#include <bits/stdc++.h>
#define ID if(1)
using namespace std;

const int maxn = 1e5 + 10;
int N , t , X , Y;
vector<int> col[maxn] , freq[maxn];
int b[maxn] , a[maxn];

int main(){
    scanf("%d" , &t);
    while(t--){
        scanf("%d %d %d" , &N , &X , &Y);
        for(int i = 0; i <= N + 1; ++i){
            a[i] = 0;
            col[i].clear();
            freq[i].clear();
        }
        for(int i = 1; i <= N; ++i){
            scanf("%d" , &b[i]);
            col[b[i]].push_back(i);
        }
        for(int i = 1; i <= N + 1; ++i){
            freq[col[i].size()].push_back(i);
        }
        int f = N + 1;
        // fix X matches first, use the most frequent color
        for(int k = 1; k <= X; ++k){
            while(freq[f].empty())--f;
            int c = freq[f].back();
            int id = col[c].back();
            a[id] = c;
            col[c].pop_back();
            freq[f].pop_back();
            freq[f - 1].push_back(c);
        }
        while(freq[f].empty())--f;
        if(N - Y < 2 * f - (N - X)){
            printf("NO\n");
            continue;
        }
        // # forced match <= N -  Y
        vector<int> pos;
        vector<bool> ok(N - X);
        for(int i = 1; i <= f; ++i){
            for(int j : freq[i]){
                for(int k : col[j]){
                    pos.push_back(k);
                }
            }
        }
        int nunmatch = N - Y;
        for(int i = 0; i < N - X; ++i){
            // shift everything by (N - X) / 2
            a[pos[i]] = b[pos[(i + (N - X) / 2) % (N - X)]]; 
            if(a[pos[i]] == b[pos[i]]){
                // a forced match, we need to replace this with color st
                // freq[color] = 0
                ok[i] = 1;
                --nunmatch;
                a[pos[i]] = freq[0][0];
            }
        }
        for(int i = 0; i < N - X && nunmatch > 0; ++i){
            if(ok[i])continue;
            a[pos[i]] = freq[0][0];
            ok[i] = 1;
            --nunmatch;
        }
        printf("YES\n");
        for(int i = 1; i <= N; ++i){
            printf("%d " , a[i]);
        }
        printf("\n");
    }
}