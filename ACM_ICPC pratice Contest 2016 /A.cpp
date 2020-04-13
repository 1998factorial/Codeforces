#include <bits/stdc++.h>
using namespace std;

int a[3],b[3];
int ans[2];
int main(){
	for(int i = 0; i < 3; i++)cin >> a[i];
	for(int i = 0; i < 3; i++)cin >> b[i];
	ans[0] = 0, ans[1] = 0;
	for(int i = 0; i < 3; i++){
		if(a[i] > b[i])ans[0]++;
		else if(a[i] < b[i])ans[1]++;
	}
	cout << ans[0] << " " << ans[1] << endl;
	return 0;
}
