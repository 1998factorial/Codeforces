#include <bits/stdc++.h>
using namespace std;

int N;
char a[300];
int cnt[5];
map<char , int> mp;
map<int , char> imp;

int main(){
    mp['A'] = 0; imp[0] = 'A';
    mp['C'] = 1; imp[1] = 'C';
    mp['G'] = 2; imp[2] = 'G';
    mp['T'] = 3; imp[3] = 'T';
    mp['?'] = 4; imp[4] = '?';
    scanf("%d" , &N);
    scanf("%s" , a + 1);
    if(N % 4){
        printf("===\n");
        return 0;
    }
    for(int i = 1; i <= N; ++i){
        ++cnt[mp[a[i]]];
    }
    int len = N / 4;
    for(int i = 0; i < 4; ++i){
        if(cnt[i] > len){
            printf("===\n");
            return 0;
        }
    }
    for(int i = 1; i <= N; ++i){
        if(a[i] != '?')continue;
        for(int j = 0; j < 4; ++j){
            if(cnt[j] < len){
                ++cnt[j];
                a[i] = imp[j];
                break;
            }
        }
    }
    printf("%s\n" , a + 1);
}