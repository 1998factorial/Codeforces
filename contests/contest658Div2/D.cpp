#include <bits/stdc++.h>
#define ID 0
using namespace std;


int N;
int p[4010];
int DP[2005];
int C[4005];

int main(){
    int t; scanf("%d" , &t);
    while(t--){
        scanf("%d" , &N);
        for(int i = 1; i <= 2 * N; ++i)scanf("%d" , &p[i]);
        vector<int> pts;
        pts.push_back(1);
        for(int i = 1 , j = 1; i <= 2 * N;){
            while(j <= 2 * N && p[j] <= p[i])++j;
            if(j <= 2 * N)pts.push_back(j);
            i = j;
        }
        if(ID){
            for(int i : pts)cout << i << " ";
            cout << endl;
        }
        for(int i = 1; i < pts.size(); ++i){
            C[i] = pts[i] - pts[i - 1];
        }
        C[pts.size()] = 2 * N - pts.back() + 1;
        if(ID)for(int i = 1; i <= pts.size(); ++i){
            printf("C[%d] = %d\n" , i , C[i]);
        }
        for(int i = 0; i <= N; ++i)DP[i] = 0;
        DP[0] = 1;
        for(int i = 1; i <= pts.size(); ++i){
            for(int j = N; j >= 0; --j){
                if(DP[j] == 1){
                    if(j + C[i] <= N){
                        DP[j + C[i]] = 1;
                    }
                }
            }
        }
        if(ID)for(int i = 0; i <= N; ++i)printf("DP[%d] = %d\n" , i , DP[i]);
        if(DP[N])printf("YES\n");
        else printf("NO\n");
    }
}