#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds ;
using namespace std ;
typedef tree <int , null_type , less <int >, rb_tree_tag ,
tree_order_statistics_node_update> ordered_set ;

const int maxn = 1e5 + 10; // TODO
int N , Q;

int a[maxn];

ordered_set S;

int cnt[maxn];

int main(){
    scanf("%d %d" , &N , &Q);
    for(int i = 1; i <= N; ++i){
        scanf("%d" , &a[i]);
        S.insert(a[i]);
        ++cnt[a[i]];
    }
    while(Q--){
        int k;
        scanf("%d " , &k);
        if(k < 0){
            --cnt[-k];
            if(cnt[-k] <= 0)
            S.erase(S.find_by_order(-k - 1));
        }
        else{
            ++cnt[k];
            S.insert(k);
        }
    }
    for(int i = 1; i <= N; ++i){
        if(S.find(i) != S.end()){
            cout << i << endl;
            return 0;
        }
    }
    cout << 0 << endl;
}
