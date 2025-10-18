#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef pair<int, int> PII;
constexpr int mod = 1e9 + 7;
constexpr int N = 2e5 + 10;
constexpr int M = N * 60;
int n, m;
void show(int num[], int len)
{
	for (int i = 1; i <= len; i++)
	{
		cout << num[i] << ' ';
	}
	cout << '\n';
}
int base[N];
vector<int> p;
bitset<N> prim;
void get_prim()
{
	prim[1] = true;
	for (int i = 2; i < N; i++)
	{
		if (!prim[i])
		{
			p.push_back(i);
			base[i] = i;
		}
		for (auto j : p)
		{
			if (j * i >= N)
			{
				break;
			}
			prim[j * i] = true;
			base[j * i] = j;
			if (i % j == 0)
			{
				break;
			}
		}
	}
}
int qpow(int a, int b)
{
	int ans = 1;
	while (b)
	{
		if (b & 1)
		{
			ans = ans * a % mod;
		}
		a = a * a % mod;
		b >>= 1;
	}
	return ans;
}
int num[N];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t = 1;
	//cin >> t;
	while (t--)
	{
		cin>>n;
		for (int i=1;i<=n;i++)
		{
			cin>>num[i];
		}
	}
}
