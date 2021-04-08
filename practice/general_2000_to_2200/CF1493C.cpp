#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
char a[maxn];
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    int t;
    cin >> t;
    while(t--){
        int N , K;
        cin >> N >> K;
        cin >> (a + 1);
        if(N % K != 0){
            cout << -1 << endl;
            continue;
        }
        vector<int> cnt(26);
        for(int i = 1; i <= N; ++i)++cnt[a[i] - 'a'];
        int ok = 1;
        for(int i = 0; i < 26; ++i)if(cnt[i] % K != 0)ok = 0;
        if(ok){
            for(int i = 1; i <= N; ++i)cout << a[i];
            cout << endl;
            continue;
        }
        // now we enumerate the longest common prefix 
        // that our answer string and a have
        ok = 0;
        for(int i = N - 1; i >= 0 && ok == 0; --i){
            //cout << "try prefix of length " << i << endl;
            --cnt[a[i + 1] - 'a'];
            for(int j = a[i + 1] - 'a' + 1; j < 26 && ok == 0; ++j){
                // now we try to put j on ans[i + 1]
                //cout << "try put j = " << (char)('a' + j) << endl;
                int min_len = 0;
                // minimal number of "pre-fixed" suffix 
                // we need to make each letter divisible by K
                vector<int> suf(26);
                for(int k = 0; k < 26; ++k){
                    if(k == j){
                        suf[k] = (K - ((cnt[k] + 1) % K)) % K; 
                    }   
                    else{
                        suf[k] = (K - (cnt[k] % K)) % K;
                    }
                    min_len += suf[k];
                }
                //cout << "min length = " << min_len << endl;
                if(min_len <= N - i - 1){
                    ok = 1;
                    // construct answer
                    for(int k = 1; k <= i; ++k)cout << a[k];
                    cout << (char)('a' + j);
                    int len_left = N - i - 1 - min_len;
                    while(len_left){
                        cout << 'a';
                        --len_left;
                    }
                    for(int k = 0; k < 26; ++k){
                        for(int l = 1; l <= suf[k]; ++l){
                            char t = 'a' + k;
                            cout << t;
                        }
                    }
                    cout << endl;
                }
            }   
        }
        if(!ok){
            cout << -1 << endl;
        }
    }
}