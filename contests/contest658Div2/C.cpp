#include <bits/stdc++.h>
using namespace std;

char a[100005] , b[100005];
int N;

int main(){
    int t; scanf("%d" , &t);
    while(t--){
        scanf("%d" , &N);
        scanf("%s" , a + 1);
        scanf("%s" , b + 1);
        vector<int> ops;
        /*for(int i = 1; i <= N; ++i){
            if(a[i] == '1')continue;
            if(i > 1)ops.push_back(i - 1);
            ops.push_back(i);
        }
        for(int i = N; i >= 1; --i){
            if(b[i] == '1')continue;
            ops.push_back(i);
            if(i > 1)ops.push_back(i - 1);
        }*/
        for(int i = 1; i < N; ++i){
            if(a[i] != a[i + 1])ops.push_back(i);
        }
        int c = a[N] - '0';
        for(int i = N; i >= 1; --i){
            if(c != b[i] - '0'){
                c = 1 - c;
                ops.push_back(i);
            }
        }
        printf("%d " , (int)ops.size());
        for(int i : ops)printf("%d " , i);
        printf("\n");
    }
}