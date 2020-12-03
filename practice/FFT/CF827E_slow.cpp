#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e5 + 10;
char s[maxn] , t[maxn];
int N;

int main(){
    int T;
    scanf("%d" , &T);
    while(T--){
        int N;
        scanf("%d" , &N);
        scanf("%s" , s);
        vector<int> periods;
        for(int d = 1; d <= N; ++d){
            for(int i = 0; i < N; ++i)t[i] = s[i];
            int ok = 1;
            for(int i = 0; i + d < N && ok; ++i){
                if(t[i] == '?' && t[i + d] == '?')continue;
                else if(t[i] == '?' && t[i + d] != '?')t[i] = t[i + d];
                else if(t[i] != '?' && t[i + d] == '?')t[i + d] = t[i];
                else if(t[i] != t[i + d])ok = 0;
            }
            if(ok)periods.push_back(d);
        }
        printf("%d\n" , (int)periods.size());
        for(int i : periods)printf("%d " , i);
        printf("\n");   
    }
}