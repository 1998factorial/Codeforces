#include <bits/stdc++.h>
#define ID if(0)
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;
char s[maxn];
int N , perm[maxn] , sum[maxn << 2];
vector<int> pos[26] , pos2[26];

void add(int pos , int val){
    while(pos <= N){
        sum[pos] += val;
        pos += pos & (-pos);
    }
}

ll get(int pos){
    ll ret = 0;
    while(pos){
        ret += sum[pos];
        pos -= pos & (-pos);
    }
    return ret;
}

int main(){
    scanf("%d" , &N);
    scanf("%s" , s + 1);
    for(int i = 1; i <= N; ++i){
        int x = s[i] - 'a';
        pos[x].push_back(i);
    }
    reverse(s + 1 , s + 1 + N);
    for(int i = 1; i <= N; ++i){
        int x = s[i] - 'a';
        pos2[x].push_back(i);
    }
    for(int i = 0; i < 26; ++i){
        for(int j = 0; j < pos[i].size(); ++j){
            perm[pos[i][j]] = pos2[i][j];
        }
    }
    ID {
        for(int i = 1; i <= N; ++i){
            printf("%d " , perm[i]);
        }
        printf("\n");
    }
    ll ret = 0; // count inversion pair
    for(int i = 1; i <= N; ++i){
        ret += get(N) - get(perm[i]);
        add(perm[i] , 1);
    }
    printf("%lld\n" , ret);
}   