#include <bits/stdc++.h>
#define ID if(0)
using namespace std;

const int maxn = 1e6 + 10;
vector<int> pt[maxn][2];
int prefix[maxn][2];
int nex[maxn][2];
int N;
char a[maxn];

int get_len(int pos , int tp){
    int l = pos , r = N , ret = -1;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(prefix[mid][1 - tp] == prefix[pos - 1][1 - tp]){
            ret = mid;
            l = mid + 1;
        }
        else{
            r = mid - 1;
        }
    }
    return ret;
}

int solve(int x){
    int ret = 0;
    int pos = 1;
    int i0 = 0 , i1 = 0;
    while(pos <= N){
        int npos0 = nex[pos][0] , npos1 = nex[pos][1];
        if(max(npos0 , npos1) - pos + 1 >= x){
            ++ret;
            pos += x; // in this case , just pick first x
        }
        else {
            // need to handle this case
            while(i0 < pt[x][0].size() && pt[x][0][i0] <= pos)++i0;
            while(i1 < pt[x][1].size() && pt[x][1][i1] <= pos)++i1;
            int np0 = (i0 < pt[x][0].size()) ? pt[x][0][i0] : N + 10;
            int np1 = (i1 < pt[x][1].size()) ? pt[x][1][i1] : N + 10;
            if(np0 > N && np1 > N)break;
            pos = min(np0 , np1); // always pick the smaller one as we need more pentential (greedy)
        }
    }
    return ret;
}

int main(){
    scanf("%d" , &N);
    scanf("%s" , a + 1);
    for(int i = 1; i <= N; ++i){
        for(int j : {0 , 1}){
            prefix[i][j] = prefix[i - 1][j];
        }
        if(a[i] != '?'){
            ++prefix[i][a[i] - '0'];
        }
    }
    for(int i = 1; i <= N; ++i){
        for(int j : {0 , 1}){
            nex[i][j] = get_len(i , j);
        }
    }
    for(int j : {0 , 1}){
        for(int i = 1; i <= N; ++i){
            if(nex[i][j] == -1)continue;
            if(i == 1 || 1 - j == a[i - 1] - '0'){ // think about coloring , and this will amortzed to O(N)
                int len = nex[i][j] - i + 1;
                for(int x = 1; x <= len; ++x){
                    pt[x][j].push_back(i);
                }
            }
        }
    }
    for(int x = 1; x <= N; ++x){
        printf("%d " , solve(x));
    }
    printf("\n");
}