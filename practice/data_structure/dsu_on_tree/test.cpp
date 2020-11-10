#include <bits/stdc++.h>
using namespace std;

int main(){
    multiset<string> s;
    s.insert("ha");
    s.insert("ha");
    s.insert("ha");
    s.insert("ha");
    s.erase(s.find("ha"));
    cout << s.count("ha") << endl;
}