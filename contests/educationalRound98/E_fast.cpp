#include <bits/stdc++.h>
#define x first 
#define y second
using namespace std;
typedef pair<int , int> pii;
int N , M , K;
pii seg[2005];
int suffix[2005];
// call mid point of fist author C1 , C2 for another author
// sort segments by their mid point, for mid point ci , if |C1 - ci| < |C2 - ci|
// then the ith participant should go to the first author's tutorial 
// we can thus conclude that optimal solution exists in 
// when some first i participants go to the first author 
// and the last N - i ones go to the second author
int inter(int l1 , int r1 , int l2 , int r2){
    int v = min(r1 , r2) - max(l1 , l2) + 1;
    return v < 0 ? 0 : v;
}

int main(){
    scanf("%d %d %d" , &N , &M , &K);
    for(int i = 1; i <= M; ++i){
        scanf("%d %d" , &seg[i].x , &seg[i].y);
    }
    sort(seg + 1 , seg + 1 + M , [&](pii& lhs , pii& rhs){
        return lhs.x + lhs.y < rhs.x + rhs.y;
    });
    for(int s1 = 1; s1 + K - 1 <= N; ++s1){
        int sum = 0;
        for(int i = M; i >= 1; --i){
            sum += max(0 , inter(s1 , s1 + K - 1 , seg[i].x , seg[i].y));
            suffix[i] = max(suffix[i] , sum);
        }
    }
    int ans = suffix[1];
    for(int s1 = 1; s1 + K - 1 <= N; ++s1){
        int sum = 0;
        for(int i = 1; i <= M; ++i){
            sum += max(0 , inter(s1 , s1 + K - 1 , seg[i].x , seg[i].y));
            ans = max(ans , sum + suffix[i + 1]);
        }
    }
    printf("%d\n" , ans);
}