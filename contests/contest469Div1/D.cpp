#include <bits/stdc++.h>
#define ID if(1)
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
ll a[maxn] , sum[maxn];
int N , D , B;

int check(int mid){ 
    // give up [1 ... mid] , [N - mid + 1 ... N]
    // a[mid + 1 , mid + 1 + 1 , .... N - mid - 1 , N - mid]
    int up = N / 2;
    for(int i = mid + 1; i <= up; ++i){ // for first instructor 
        int rb = min((ll)N , (ll)i + (ll)i * D);
        ll left_val = sum[i] - (i - mid - 1) * B; // ppl from left
        ll right_val = (sum[rb] - sum[i]); // ppl from right
        if(left_val + right_val < B)return 0;
        int j = N - i + 1; // right index
        int lb = max(1ll , (ll)j - (ll)i * D);
        right_val = sum[N] - sum[j] - (ll)B * (i - mid - 1);
        left_val = sum[j] - sum[lb - 1];
        if(left_val + right_val < B)return 0;
    }
    return 1;
}

int main(){
    scanf("%d %d %d" , &N , &D , &B);
    for(int i = 1; i <= N; ++i){
        scanf("%lld" , &a[i]);
        sum[i] = sum[i - 1] + a[i];
    }
    int l = 0 , r = N / 2 , ans = N / 2;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(check(mid)){
            ans = mid;
            r = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }
    printf("%d\n" , ans);
}