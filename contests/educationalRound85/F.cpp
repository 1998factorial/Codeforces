/*
    Dynamic programming, optimization
    First, b must be a strict ascending sequence
    Now, consider our subproblem:
    DP[j] = "minimal cost to make b[1 ... j] from a, such that the largest element in a will not excceed b[j]"
    clearly, when we are checking if a[i] can be kept as b[j] (assuming a[i] == b[j]),
    we need to remove all elements in a[1 ... i - 1] that excceed b[j - 1] and do not excced b[j] as these elements do
    not belong to the configuration of DP[j - 1] (as they excceed b[j - 1]) and could be considered in array b by the
    definition of funciton f. (as they do not excceed b[j])
    to find all these elements' cost efficiently, we can sweep from 1 to N, using lower bound to query smallest j
    that are no less than a[i] in b, so that, their cost will only be added when considering a leap from DP[j - 1] to DP[j]

    Also, we should try to remove as many negative cost elements as possible
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5e5 + 10;
const ll inf = 1e18;
ll a[maxn] , b[maxn] , p[maxn];
ll DP[maxn]; // DP[j] =  minimal cost to make b[1 .. j] from subsequence of a st all elements in this subsequence do not excceed b[j]
ll cost[maxn]; // cost[j] = cost to append b[j] after b[j - 1] so far
int N , M;

int main(){
    scanf("%d" , &N);
    for(int i = 1; i <= N; ++i){
        scanf("%lld" , &a[i]);
    }
    for(int i = 1; i <= N; ++i){
        scanf("%lld" , &p[i]);
    }
    scanf("%d" , &M);
    for(int i = 1; i <= M; ++i){
        scanf("%lld" , &b[i]);
    }
    b[M + 1] = inf; // add largest value at the end, so DP[M] + cost[M + 1] will have the answer
    for(int i = 1; i <= N; ++i){
        int j = lower_bound(b + 1 , b + 2 + M , a[i]) - b;
        if(p[i] < 0){
            cost[j] += p[i];
        }
    }
    for(int j = 1; j <= M; ++j){
        DP[j] = inf;
    }
    DP[0] = 0;
    for(int i = 1; i <= N; ++i){
        int j = lower_bound(b + 1 , b + 2 + M , a[i]) - b;
        if(j <= M){
            if(a[i] == b[j]){
                if(p[i] < 0){
                    DP[j] = min(DP[j] , DP[j - 1] + cost[j] - p[i]); // subtract back the already counted discount
                }
                else{
                    DP[j] = min(DP[j] , DP[j - 1] + cost[j]);
                }
            }
            if(p[i] > 0){
                cost[j] += p[i]; // only for the positive costs, as we have already counted the negative ones
            }
        }
        else if(p[i] > 0){
            cost[j] += p[i];
        }
    }
    if(DP[M] > 1e14){ // overlimit , meaning we can not reach DP[M] from DP[0]
        printf("NO\n");
    }
    else{
        printf("YES\n%lld\n" , DP[M] + cost[M + 1]);
    }
}
