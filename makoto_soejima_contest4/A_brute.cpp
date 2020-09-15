#include <bits/stdc++.h>
#define ID if(1)
#define x first
#define y second
using namespace std;
typedef long long ll;
const ll lim = 1e18;
ll K;

int D(int x){
    map<int , int> cnt;
    for(int i = 2; i * i <= x; ++i){
        if(x % i == 0){
            while(x % i == 0){
                ++cnt[i];
                x /= i;
            }
        }
    }
    if(x > 1){
        ++cnt[x];
    }
    int ret = 1;
    for(auto& e : cnt){
        ret *= (1 + e.second);
    }
    return ret;
}

ll solve(){
    vector<int> vec;
    for(int x = 1; x <= 2000; ++x){
        int cnt = 0;
        for(int y = x - 1; y ; --y){
            if(D(y) > D(x)){
                ++cnt;    
            }
        }        
        if(cnt <= 1){
            vec.push_back(x);
        }
    }
    printf("there are %d divisorful numbers \n" , (int)vec.size());
    printf("show divisorful numbers : ");
    for(int x : vec){
        printf("%d " , x);
    }
    printf("\n");
    printf("show differences ");
    for(int i = 0; i < vec.size() - 1; ++i){
        printf("%d " , vec[i + 1] - vec[i]);
    }
    printf("\n");

    return 0;
}
int main(){
    scanf("%lld" , &K);
    printf("%lld\n" , solve());
}