#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int N , a[maxn] , b[maxn];

bool check(int len , int i){
    int l = max(a[i] , a[i - len + 1]);
    int r = min(b[i] , b[i - len + 1]);
    return r - l + 1 >= len;
}

int main(){
    scanf("%d" , &N);
    int ans = 0;
    for(int i = 1; i <= N; ++i){
        scanf("%d %d" , &a[i] , &b[i]);
        ++a[i]; ++b[i];
        int l = 1 , r = i , sz = 1;
        while(l <= r){
            int mid = (l + r) >> 1;
            if(check(mid , i)){
                sz = mid;
                l = mid + 1;
            }
            else r = mid - 1;
        }
        ans = max(ans , sz);
    }
    printf("%d\n" , ans);
}