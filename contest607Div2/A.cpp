#include <iostream>
#include <cstring>
using namespace std;

int main(){
  int N;
  cin >> N;
  for(int i = 1; i <= N; ++i){
    string s; cin >> s;
    int n = s.size();
    if(s[n - 1] == 'o' && s[n - 2] == 'p')cout << "FILIPINO" << endl;
    if(s[n - 1] == 'u' && s[n - 2] == 's'&& s[n - 3] == 'e' && s[n - 4] == 'd')cout << "JAPANESE" << endl;
    if(s[n - 1] == 'u' && s[n - 2] == 's'&& s[n - 3] == 'a' && s[n - 4] == 'm')cout << "JAPANESE" << endl;
    if(s[n - 1] == 'a' && s[n - 2] == 'd'&& s[n - 3] == 'i' && s[n - 4] == 'n' && s[n - 5] == 'm')cout << "KOREAN" << endl;
  }
}
