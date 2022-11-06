#define _CRT_SECURE_NO_WARNINGS 1
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl "\n"
const int INF = 0x3f3f3f3f;
const int N = 2e5 + 100;
void mymin()
{
	int n, a;//当A拿到最小数，那他的操作是最小数-1，然后换了个数，到了b，肯定一直把最小数放到a1，那么A就一直接受最小数（且只能减他），而b不会，b必定赢
	cin >> n;//相反，当A第一次不是拿最小数，他肯定把最小数放a1，这样B就要一直接受最小数，那么A必定赢
	int flag = 1;
	int minn;
	for (int i = 1; i <= n; ++i)
		{
			cin >> a;
			if (i == 1)minn = a;
			else if (minn > a)flag = 0;
		}
	if (flag)cout << "BOB" << endl;
	else cout << "ALICE" << endl;
}
int main()
{
	int t;
	cin >> t;
	while (t--)
		{
			mymin();
		}
	system("pause");
	return 0;
}
