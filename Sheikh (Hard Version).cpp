#include <bits/stdc++.h>

using namespace std;
#define ll long long

const int N = 2e5 + 100;
//俩边同时逼近
ll a[N];
ll sum[N];
ll xm[N];
ll mleft[N];
ll mright[N];
//首先，明确取反x是最多不可能增加多余x的，所以保证f(l,r)<=f(l,r+1)，即只要数串越长，绝对值越大，不可能会小

ll f(ll l, ll r) //计算l到r的值
{
    return sum[r] - sum[l - 1] - (xm[r] ^ xm[l - 1]);
}

void mymin()
{
    ll n, q;
    cin >> n >> q;
    for (ll i = 1; i <= n; ++i)
    {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
        xm[i] = xm[i - 1] ^ a[i];
        mleft[i] = a[i] == 0 ? mleft[i - 1] : i; //用于r的逼近，left是只要你为0，就取前面的，保证数组存的每个值都是有数值的，
                                                 //这样当r向左移动时，如果本来是0，因为数组村的是离左边最近不是0的值，就会直接跑到那里，避免一步一步浪费时间
    }
    mright[n + 1] = n + 1;       //但是右边初始是0，不可能是瞬移到左边，所以给右边界外的n+1赋值，避免跑左边去
    for (int i = n; i >= 1; --i) // right用于左边l向右移动，同理
        mright[i] = a[i] == 0 ? mright[i + 1] : i;
    while (q--)
    {
        ll L, R;
        cin >> L >> R;
        ll l = L, r = R;  //输入的L，R，但是输出是l，r，因为需要保留L，R不变，后面有作用
        ll ans = f(L, R); //计算L，R区间的最大值

        if (ans == 0) //如果数串都为0，那取区间为1就好，也是0而且最短
        {
            cout << l << " " << l << endl;
            continue;
        }
        ll i = L;                        // i，j用来逼近，逼近成功就存给l，r，而初始的L，R作为限制
        while (i <= R && f(i, R) == ans) //保证每次i不超过初始右边界且一直i与R的区间是等于ans
        {
            ll j = R;      //即使r向左逼近成功变小，每个i更新后的j仍然初始为R，你不能排除我左边推到R可能会比r逼近左边更小的可能性
            while (i <= j) //条件当然是i小于j才能继续
            {
                if (f(i, j) == ans)
                {
                    if (r - l > j - i) //必须保证长度比储存的小，我才更新，只是等于还不可以，而且不能跟上面if写一起，不一定要同时成立，第一个if成立，就能往下继续循环
                    {                  //如果一起，就会减少情况的考虑
                        l = i;
                        r = j;
                    }
                }
                else //不符合第一个if那肯定跳出
                    break;
                j = mleft[j - 1]; //能执行第一个if，j就可以向左逼近
            }
            i = mright[i + 1]; //出来一次里面的while就可以i继续向右逼近，而且每次i右逼近，j都重新为R，也就是i右移一次，j遍历
        }
        cout << l << " " << r << endl;
    }
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

// C2. Sheikh (Hard Version)
// 题目大意:
// 这是该问题的困难版本。唯一不同的是，在这个版本中q=n。

// 你将得到一个整数数组a1,a2,…,an。

// 数组[l,r]的一个子段的成本，1≤l≤r≤n，是值f(l,r)=sum(l,r)-xor(l,r)，其中sum(l,r)=al+al+1+…+ar，xor(l,r)=al⊕al+1⊕…⊕ar（⊕代表位向XOR）。

// 你将有q个查询。每个查询由一对数字Li, Ri给出，其中1≤Li≤Ri≤n。你需要找到具有最大值f(l,r)的子段[l,r]，Li≤l≤r≤Ri。如果有几个答案，那么你需要在其中找到一个长度最小的子段，也就是r-l+1的最小值。

// 输入
// 每个测试由多个测试案例组成。第一行包含一个整数t（1≤t≤10^4）–测试案例的数量。测试用例的描述如下。

// 每个测试用例的第一行包含两个整数n和q（1≤n≤10^5，q=n）–阵列的长度和查询次数。

// 每个测试用例的第二行包含n个整数a1,a2,…,an (0≤ai≤10^9) - 数组元素。

// 每个测试案例接下来的q行中的第i行包含两个整数Li和Ri（1≤Li≤Ri≤n）–我们需要在其中找到段的边界。

// 保证所有测试案例的n之和不超过2⋅10^5。

// 保证L1=1，R1=n。

// 输出
// 对于每个测试案例，打印q对数字Li≤l≤r≤Ri，使f(l,r)的值最大，并且其中r-l+1的长度最小。如果有几个正确的答案，打印其中任何一个。
