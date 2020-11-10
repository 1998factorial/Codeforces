#include <bits/stdc++.h>
using namespace std;

int main(){
    int i = 1; 
    for(int j = 1; j <= 1008; ++j){
        i *= 3;
        i %= 1009;
    }
    cout << i << endl;
}