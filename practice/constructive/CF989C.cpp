/*
    Constructive
    claim: we can always do so using a 50 by 50 matrix
    from [1 , 1] to [25 , 25] are all A
    from [1 , 26] to [25 , 50] are all B
    from [26 , 1] to [50 , 25] are all C
    from [26 , 26] to [50 , 50] are all D

    we place extra Ds in area of A, place extra As in area of D
    similarly for B and C

    If we place them alternativly, then for each row, we place at least 12
    and there are at least 12 rows for each area that we can place
    which means that we can create for each type, an extra of 144 connected components
    which is certainly sufficent for a , b , c , d <= 100
*/

#include <bits/stdc++.h>
using namespace std;

char ans[55][55];

int a , b , c , d;

int main(){
    cin >> a >> b >> c >> d;
    --a , --b , --c , --d;
    for(int i = 1; i <= 25; ++i){
        for(int j = 1; j <= 25; ++j){
            ans[i][j] = 'A';
        }
    }
    for(int i = 1; i <= 25; ++i){
        for(int j = 26; j <= 50; ++j){
            ans[i][j] = 'B';
        }
    }
    for(int i = 26; i <= 50; ++i){
        for(int j = 1; j <= 25; ++j){
            ans[i][j] = 'C';
        }
    }
    for(int i = 26; i <= 50; ++i){
        for(int j = 26; j <= 50; ++j){
            ans[i][j] = 'D';
        }
    }
    // place D in A
    for(int i = 1; i <= 25 && d > 0; i += 2){
        for(int j = 1; j <= 25 && d > 0; j += 2){
            ans[i][j] = 'D';
            --d;
        }
    }
    // place C in B
    for(int i = 1; i <= 25 && c > 0; i += 2){
        for(int j = 26; j <= 50 && c > 0; j += 2){
            ans[i][j] = 'C';
            --c;
        }
    }
    // place B in C
    for(int i = 26; i <= 50 && b > 0; i += 2){
        for(int j = 1; j <= 25 && b > 0; j += 2){
            ans[i][j] = 'B';
            --b;
        }
    }
    // place D in D
    for(int i = 26; i <= 50 && a > 0; i += 2){
        for(int j = 26; j <= 50 && a > 0; j += 2){
            ans[i][j] = 'A';
            --a;
        }
    }
    cout << 50 << " " << 50 << endl;
    for(int i = 1; i <= 50; ++i){
        for(int j = 1; j <= 50; ++j){
            cout << ans[i][j];
        }
        cout << endl;
    }
}
