#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int sum[maxn << 2] , N , K , R;

void add(int pos , int val){
    while(pos <= N){
        sum[pos] += val;
        pos += pos & (-pos);
    }
}

int query(int pos){
    int ret = 0;
    while(pos){
        ret += sum[pos];
        pos -= pos & (-pos);
    }
    return ret;
}

int range(int l , int r){
    return query(r) - query(l - 1);
}

int main(){
    scanf("%d %d %d" , &N , &K , &R);
    for(int i = 1; i <= K; ++i){
        int x;
        scanf("%d" , &x);
        add(x , 1);
    }
    int ret = 0;
    for(int i = 1; i + R - 1 <= N; ++i){
        int s = range(i , i + R - 1);
        if(s >= 2)continue;
        if(s == 0){
            ret += 2;
            add(i + R - 1 , 1);
            add(i + R - 2 , 1);
            continue;
        }
        ret += 1;
        if(range(i + R - 1 , i + R - 1) >= 1){
            add(i + R - 2 , 1);
        }
        else{
            add(i + R - 1 , 1);
        }
    }
    printf("%d\n" , ret);
}