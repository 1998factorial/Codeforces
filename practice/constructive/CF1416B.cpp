#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    scanf("%d" , &t);
    while(t--){
        int N;
        scanf("%d" , &N);
        vector<int> a(N + 1);
        int sum = 0;
        for(int i = 1; i <= N; ++i){
            scanf("%d" , &a[i]);
            sum += a[i];
        }
        if(sum % N != 0){
            printf("-1\n");
            continue;
        }
        vector<vector<int>> ans;
        for(int i = 2; i <= N; ++i){
            if(a[i] % i == 0){
                ans.push_back({i , 1 , a[i] / i});
            }
            else{
                int m = i - a[i] % i;
                ans.push_back({1 , i , m}); // a[1] >= i - 1 now
                ans.push_back({i , 1 , (a[i] + m) / i});
            }
        }
        for(int i = 2; i <= N; ++i){
            ans.push_back({1 , i , sum / N});
        }
        printf("%d\n" , (int)ans.size());
        for(vector<int>& v : ans){
            printf("%d %d %d\n" , v[0] , v[1] , v[2]);
        }
    }   
}