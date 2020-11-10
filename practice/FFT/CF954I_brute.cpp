#include <bits/stdc++.h>
#define ID if(1)
using namespace std;
const int maxn = 125005;
char S[maxn] , T[maxn];
int N , M;
vector<int> cnt;
vector<int> fa;

int find(int i){
    return fa[i] == i ? i : fa[i] = find(fa[i]);
}

void merge(int i , int j){
    i = find(i);
    j = find(j);
    fa[i] = j;
}

int main(){
    scanf("%s" , S + 1);
    scanf("%s" , T + 1);
    N = strlen(S + 1);
    M = strlen(T + 1);
    for(int i = 1; i <= N - M + 1; ++i){
        int ans = 0;
        fa = vector<int> (7 , -1);
        cnt = vector<int> (7 , 0);
        for(int j = 1; j <= M; ++j){
            ++cnt[S[i + j - 1] - 'a' + 1]; 
            ++cnt[T[j] - 'a' + 1];
        }
        for(int i = 1; i <= 6; ++i)fa[i] = i;
        for(int j = 1; j <= M; ++j){
            if(S[i + j - 1] != T[j]){
                if(find(S[i + j - 1] - 'a' + 1) != find(T[j] - 'a' + 1))
                    merge(S[i + j - 1] - 'a' + 1 , T[j] - 'a' + 1) , ++ans;
            }
        }
        printf("%d " , ans);
    }
    printf("\n");
}