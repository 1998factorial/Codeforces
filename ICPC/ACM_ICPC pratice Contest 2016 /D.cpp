#include <bits/stdc++.h>
using namespace std;

int a[10];
int t[10];

bool check(){
    return
    a[1] + a[2] + a[3] == 15 &&
    a[4] + a[5] + a[6] == 15 &&
    a[7] + a[8] + a[9] == 15 &&
    a[1] + a[4] + a[7] == 15 &&
    a[2] + a[5] + a[8] == 15 &&
    a[3] + a[6] + a[9] == 15 &&
    a[1] + a[5] + a[9] == 15 &&
    a[3] + a[5] + a[7] == 15;
}

int main(){
    for(int i = 1; i <= 9; ++i)a[i] = i;
    for(int i = 1; i <= 9; ++i)cin >> t[i];
    int ret = 10000;
    do{
        if(check()){
            int val = 0;
            for(int i = 1; i <= 9; ++i)val += abs(a[i] - t[i]);
            ret = min(ret , val);
        }
    }while(next_permutation(a + 1 , a + 10));
    cout << ret << endl;
}
