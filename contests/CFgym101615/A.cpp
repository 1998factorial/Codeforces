#include <bits/stdc++.h>
using namespace std;
char s[105];
int N;
int isp[105][105];

int main(){
    scanf("%s" , (s + 1));
    N = strlen(s + 1);
    for(int i = 1; i <= N; ++i)isp[i][i] = 1;
    for(int i = 1; i < N; ++i){
        isp[i][i + 1] = (s[i] == s[i + 1]);
    }
    for(int len = 3; len <= N; ++len){
        for(int i = 1; i + len - 1 <= N; ++i){
            int j = i + len - 1;
            isp[i][j] = isp[i + 1][j - 1] && (s[i] == s[j]);
        }
    }
    int ok = 1;
    for(int i = 1; i <= N; ++i){
        for(int j = i; j <= N; ++j){
            if(!isp[i][j])continue;
            int len = j - i + 1;
            if(len % 2 == 0)ok = 0;
        }
    }
    if(ok){
        printf("Odd.\n");
    }
    else{
        printf("Or not.\n");
    }
}