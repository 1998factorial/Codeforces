#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 5000005;
ll W;
int N;

int main(){
    scanf("%lld" , &W);
    scanf("%d" , &N);
    ll area = 0;
    for(int i = 1; i <= N; ++i){
        ll w , l;
        scanf("%lld %lld" , &w , &l);
        area += w * l;
    }
    printf("%lld\n" , area / W);
}