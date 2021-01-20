#include <bits/stdc++.h>
using namespace std;
const int maxn = 500005;
string text;
int len[maxn] , N = 0 , sum[maxn];

int solve(int x){
    int i = 1 , ret = 0 , cnt = 0;
    while(i <= N){
        int l = i + 1 , r = N , nex = i;
        while(l <= r){
            int mid = (l + r) >> 1;
            if(sum[mid] - sum[i - 1] + (mid - i) <= x){
                nex = mid;
                l = mid + 1;
            }
            else r = mid - 1;
        }
        ret += len[i];
        ++cnt;
        i = nex + 1;
    }
    return ret + cnt - 1;
}

int main(){
    char c;
    int cnt = 0;
    while((c = getchar()) != '\n'){
        if(c == ' '){
            if(cnt)len[++N] = cnt;
            cnt = 0;
        }
        else ++cnt;
    }
    if(cnt)len[++N] = cnt;
    for(int i = 1; i <= N; ++i)sum[i] = sum[i - 1] + len[i];
    int L , R;
    scanf("%d %d" , &L , &R);
    for(int i = L; i <= R; ++i){
        printf("%d\n" , solve(i));
    }
}   