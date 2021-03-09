#include <bits/stdc++.h>
using namespace std;
int a , b , k;
// a 0s , b 1s
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> a >> b >> k;
    if(a == 0 || b == 1){
        if(k == 0){
            cout << "Yes" << endl;
            for(int i = 1; i <= b; ++i)cout << 1;
            for(int i = 1; i <= a; ++i)cout << 0;
            cout << endl;
            for(int i = 1; i <= b; ++i)cout << 1;
            for(int i = 1; i <= a; ++i)cout << 0;
            cout << endl;
            exit(0);
        }
        else{
            cout << "No" << endl;
            exit(0);
        }
    }
    if(k > a + b - 2){
        cout << "No" << endl;
        exit(0);
    }
    cout << "Yes" << endl;
    for(int i = 1; i <= b; ++i)cout << 1;
    for(int i = 1; i <= a; ++i)cout << 0;
    cout << endl;
    if(k <= a){
        for(int i = 1; i < b; ++i)cout << 1;
        for(int i = 1; i <= k; ++i)cout << 0;
        cout << 1;
        for(int i = 1; i <= a - k; ++i)cout << 0;
        cout << endl;
        exit(0);
    }
    for(int i = 1; i <= a + b; ++i){
        if(i < a + b - k){
            cout << 1;
        }
        else if(i == a + b - k){
            cout << 0;
        }
        else if(i <= b){
            cout << 1;
        }
        else if(i < a + b){
            cout << 0;
        }
        else{
            cout << 1;
        }
    }
    cout << endl;
}
