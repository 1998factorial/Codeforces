#include <bits/stdc++.h>
using namespace std;

const int maxn = 100005;
char s[maxn];
int d[maxn] , N;
bool vis[maxn];

int main(){
    int i;
    scanf("%d" , &N);
    scanf("%s" , s + 1);
    for(int i = 1; i <= N; ++i)scanf("%d" , &d[i]);
    for(i = 1; i >= 1 && i <= N; ){
        vis[i] = 1;
        int sign = s[i] == '>' ? 1 : -1;
        i += sign * d[i];
        if(i >= 1 && i <= N && vis[i]){
            printf("INFINITE\n");
            return 0;
        }
    }
    printf("FINITE\n");
}