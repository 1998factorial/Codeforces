#include <iostream>
using namespace std;


int main() {
  int a, d, m;
  int g, p, b;
  cin >> a >> d >> m;
  cin >> g >> p >> b;
  int gl = g - a;
  int pl = gl + p - d;
  int ml = pl + b - m;
  if(gl < 0 || pl < 0 || ml < 0)
    cout << "NO" << endl;
  else
    cout << "YES" << endl;

  return 0;
}
