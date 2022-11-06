#define _CRT_SECURE_NO_WARNINGS 1
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl "\n"
const int INF = 0x3f3f3f3f;
const int N = 2e5 + 100;
//对区间操作，显然是前缀和知识
//因为每次选取一段奇数长度的区间替换为区间异或和，那么改变前后这个区间异或和不变，注意，最终要全部为0，即整段区间异或和为0，又因为怎么操作也不能改变区间异或和的值，所以只有一开始区间异或和xor（l，r）==0才可能有解
//在此前提，如果（l,r)长度为奇数，那直接对整段操作1次就ok
//如果偶数，但是a[l]或者a[r]有一个为0，那么区间有效长度还是奇数，仍然一步就可以
//最后，如果还是偶数，那么我需要把他分为俩段奇数段（当然可以分解为多段，但是我要操作数最小），使xor(l,i),xor(i+1,r)都为0，怎么找到i呢
//如果前k个数字的异或和为h，后面k+n又出现一次异或和为h，那么中间这段长度为n的异或和为0，所以我们可以通过map来寻找
//从1到n，我们每次对当前xor（假设当前i为奇数，偶数同理）判断，如果前面有出现过长度为偶数的点k，且xor也是这个值，我们用last[i]存储距离i最近的k，表示xor（k，i）==0
//而且每次i操作最后都标记	mp[i % 2][xsum[i]] = i;，即记录这个奇数（偶数）情况下存在过这个异或和，最后一次出现的位置为点i，保证每次更新一直向右靠近
//我们map开俩组就好，一个奇数，一个偶数，即mp[0][xor],mp[1][xor],储存的是最后一次出现这个xor值且位置为奇数（偶数）的点i
ll xsum[N];
ll sum[N];
ll a[N];
ll last[N];
void mymin()
{
	int n, q;
	cin >> n >> q;
	for (int i = 1; i <= n; ++i)
		{
			cin >> a[i];
			sum[i] = sum[i - 1] + a[i];
			xsum[i] = xsum[i - 1] ^ a[i];
		}
	map<ll, ll>mp[2];
	for (int i = 1; i <= n; ++i)
		{
			if (mp[(i + 1) % 2].count(xsum[i]))last[i] = mp[(i + 1) % 2][xsum[i]];
			mp[i % 2][xsum[i]] = i;
		}
	while (q--)
		{
			ll l, r;
			cin >> l >> r;
			if ((xsum[r]^xsum[l - 1]) == 0)
				{
					if (sum[r] - sum[l - 1] == 0)cout << 0 << endl;
					else if ((r - l + 1) & 1)cout << 1 << endl;
					else if (!a[l] || !a[r])cout << 1 << endl;
					else if (last[r] >= l)cout << 2 << endl;
					else cout << -1 << endl;
				}
			else cout << -1 << endl;
		}
}
int main()
{
	std::ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
//	int t;
//	cin >> t;
//	while (t--)
//		{
	mymin();
	//	}
	system("pause");
	return 0;
}
