#include <bits/stdc++.h>
using namespace std;

int main(){
    int x1 , x2 , y1 , y2;
    cin >> x1 >> y1 >> x2 >> y2;
    if(x1 + y1 <= max(x2 , y2) + 1){
        cout << "Polycarp\n";
    }
    else{
        cout << "Vasiliy\n";
    }
}