#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
const int maxn = 2e5 + 10;
int N , M;
int a[maxn];
int k[maxn];
int cnt[maxn];

int main(){
    int i , j;
    scanf("%d %d" , &N , &M);
    int min_len = 0 , to_count = 0;
    for(i = 1; i <= N; ++i)scanf("%d" , &a[i]);
    for(i = 1; i <= M; ++i)scanf("%d" , &k[i]) , min_len += k[i] , to_count += (k[i] > 0);
    int f = 0 , ans = N;
    for(i = 1 , j = 1; i <= N; ++i){
        ++cnt[a[i]];
        if(cnt[a[i]] == k[a[i]])--to_count;
        if(!to_count){ // for this i , find the maximal j st  a[i .. j] is still good
            ID printf("here at [%d %d] we are ok\n" , j , i);
            while(j <= N){
                if(cnt[a[j]] - 1 < k[a[j]])break; // j is the maximal 
                --cnt[a[j]];
                ++j;
            }
            ID printf("at the end at [%d %d] we are ok\n" , j , i);
            ans = min(ans , i - j + 1);
            f = 1;
        }
    }
    if(f){
        printf("%d\n" , ans - min_len);
    }
    else{
        printf("-1\n");
    }
}