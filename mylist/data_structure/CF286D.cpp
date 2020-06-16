/*
    sweep line , rating 2600
    I got the y-tgraph an then I lost it.
    So I bowed to solution

*/
#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5 + 10;
int L[maxn];
int l[maxn] , r[maxn] , t[maxn] , q[maxn];
int b[maxn] , k[maxn];
vector<int> add[maxn] , del[maxn];
int N , M;

inline int read(){ // fast read
    int x = 0 , f = 1 , c = getchar();
    for(; !isdigit(c); c = getchar()){
        if(c == '-'){
            f = -1;
        }
    }
    for(; isdigit(c); c = getchar()){
        x = x * 10 + c - '0';
    }
    return x * f;
}

int main(){
    int tot = 0;
    N = read() , M = read();
    for(int i = 1; i <= M; ++i){
        L[++tot] = l[i] = read();
        L[++tot] = r[i] = read();
        t[i] = read();
    }
    for(int i = 1; i <= N; ++i){
        L[++tot] = q[i] = read();
    }
    sort(L + 1 , L + 1 + tot);
    tot = unique(L + 1 , L + 1 + tot) - L - 1;
    for(int i = 1; i <= M; ++i){
        l[i] = lower_bound(L + 1 , L + 1 + tot , l[i]) - L;
        r[i] = lower_bound(L + 1 , L + 1 + tot , r[i]) - L;
        add[l[i]].push_back(t[i]);
        del[r[i]].push_back(t[i]);
    }
    for(int i = 1; i <= N; ++i){
        q[i] = lower_bound(L + 1 , L + 1 + tot , q[i]) - L;
    }
    multiset<int> s;
    for(int i = 1; i < tot; ++i){
        for(int j : add[i]){
            s.insert(j);
        }
        for(int j : del[i]){
            s.erase(s.find(j));
        }
        if(!s.empty()){
            int time = *s.begin();
            int x = L[i] , y = L[i + 1];
            //printf("time at [%d %d] = %d\n" , x , y , time);
            int pos_s = lower_bound(L + 1 , L + 1 + tot , time - y) - L;
            int pos_t = lower_bound(L + 1 , L + 1 + tot , time - x) - L;
            b[pos_s] += y - time;
            //printf("b[%d] += %d\n" , pos_s , y - time);
            b[pos_t] += time - x;
            //printf("b[%d] += %d\n" , pos_t , time - x);
            k[pos_s]++;
            //printf("k[%d] ++\n" , pos_s);
            k[pos_t]--;
            //printf("k[%d] --\n" , pos_t);
        }
    }
    for(int i = 1; i <= tot; ++i){
        //printf("b[%d] = %d\n" , i , b[i]);
        //printf("k[%d] = %d\n" , i , k[i]);
        b[i] += b[i - 1];
        k[i] += k[i - 1];
    }
    //for(int i = 1; i <= tot; ++i){
    //    printf("b[%d] = %d\n" , i , b[i]);
    //    printf("k[%d] = %d\n" , i , k[i]);
    //}
    for(int i = 1; i <= N; ++i){
        printf("%d\n" , k[q[i]] * L[q[i]] + b[q[i]]);
    }
}
