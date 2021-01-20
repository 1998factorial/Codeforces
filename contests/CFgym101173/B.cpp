#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N , M , ga[20] , gb[20] , na[1 << 20] , nb[1 << 20] , gooda[1 << 20] , goodb[1 << 20];
ll va[20] , vb[20] , T , fa[1 << 20] , fb[1 << 20];
// vamask[mask] = mask is subset of A and f(mask)
char s[20];

int main(){
    scanf("%d %d" , &N , &M);
    for(int i = 0; i < N; ++i){
        scanf("%s" , s);
        for(int j = 0; j < M; ++j){
            if(s[j] == '1'){
                ga[i] |= (1 << j);
                gb[j] |= (1 << i);
            }
        }
    }
    for(int i = 0; i < N; ++i){
        scanf("%lld" , &va[i]);
    }
    for(int i = 0; i < M; ++i){
        scanf("%lld" , &vb[i]);
    }
    scanf("%lld" , &T);
    for(int mask = 0; mask < 1 << N; ++mask){
        for(int i = 0; i < N; ++i){
            if(mask >> i & 1){
                fa[mask] += va[i];
                na[mask] |= ga[i];
            }
        }
    }
    for(int mask = 0; mask < 1 << M; ++mask){
        for(int i = 0; i < M; ++i){
            if(mask >> i & 1){
                fb[mask] += vb[i];
                nb[mask] |= gb[i];
            }
        }
    }
    vector<int> Asubset , Bsubset;
    // if x (subset of A) is a subset of some matching
    // and y (subset of B) is a subset of some matching 
    // then x union y is also a subset of some matching
    gooda[0] = 1;
    for(int mask = 1; mask < 1 << N; ++mask){
        if(__builtin_popcount(mask) > __builtin_popcount(na[mask]))continue;
        gooda[mask] = 1;
        for(int i = 0; i < N; ++i){
            if(mask >> i & 1){
                gooda[mask] &= gooda[mask ^ (1 << i)];
            }
        }
    }
    goodb[0] = 1;
    for(int mask = 1; mask < 1 << M; ++mask){
        if(__builtin_popcount(mask) > __builtin_popcount(nb[mask]))continue;
        goodb[mask] = 1;
        for(int i = 0; i < M; ++i){
            if(mask >> i & 1){
                goodb[mask] &= goodb[mask ^ (1 << i)];
            }
        }
    }
    for(int mask = 0; mask < 1 << N; ++mask){
        if(gooda[mask])Asubset.push_back(mask);
    }
    for(int mask = 0; mask < 1 << M; ++mask){
        if(goodb[mask])Bsubset.push_back(mask);
    }
    sort(Asubset.begin() , Asubset.end() , [&](int l , int r){
        return fa[l] < fa[r];
    });
    sort(Bsubset.begin() , Bsubset.end() , [&](int l , int r){
        return fb[l] < fb[r];
    });
    ll ret = 0;
    for(int i : Asubset){
        int l = 0 , r = Bsubset.size() - 1 , pos = r + 1;
        while(l <= r){
            int mid = (l + r) >> 1;
            // check for Bsubset[mid] >= T - fa[i]
            if(fb[Bsubset[mid]] >= T - fa[i]){
                pos = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }
        if(pos == Bsubset.size())continue;
        ret += Bsubset.size() - pos;
    }
    printf("%lld\n" , ret);
}