#include <bits/stdc++.h>
using namespace std;

void show(int x){
    for(int i = 10; i >= 0; --i){
        if(x & (1 << i))cout << 1;
        else cout << 0;
    }
    cout << endl;
}

// 19 , 122 -> 1111111
// 10 , 13 -> 1101

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    for(int l = 1; l <= 32; ++l){
        for(int r = l; r <= 32; ++r){
            int ret = 0;
            for(int x = l; x <= r; ++x){
                for(int y = x; y <= r; ++y){
                    int v = 0;
                    for(int z = x; z <= y; ++z){
                        v ^= z;
                    }
                    if(v > ret){
                        ret = v;
                    }
                }
            }
            int ok = 0;
            int hl = 10 , hr = 10;
            while(hl >= 0 && (l >> hl & 1) == 0)--hl;
            while(hr >= 0 && (r >> hr & 1) == 0)--hr;
            if(hl != hr)continue;
            cout << "show set : \n";
            show(l);
            show(r);
            cout << "ans = "; 
            show(ret);
        }
    }
}