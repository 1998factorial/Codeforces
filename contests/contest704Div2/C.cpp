#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int N , M , rightmost[maxn] , leftmost[maxn];
char s[maxn] , t[maxn];
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    cin >> (s + 1);
    cin >> (t + 1);
    for(int i = M , j = N; i >= 1; --i){
        while(s[j] != t[i] && j >= 1)--j;
        rightmost[i] = j;
        --j;
        //printf("rightmost[%d] = %d\n" , i , rightmost[i]); 
    }
    for(int i = 1 , j = 1; i <= M; ++i){
        while(s[j] != t[i] && j <= N)++j;
        leftmost[i] = j;
        ++j;
        //printf("leftmost[%d] = %d\n" , i , leftmost[i]);
    }
    int ans = 0;
    for(int i = 1; i < M; ++i){
        ans = max(ans , rightmost[i + 1] - leftmost[i]);
    }
    cout << ans << endl;
}
