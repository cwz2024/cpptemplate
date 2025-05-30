int qpow(int a, long long n, int mod)
{
	int ans = 1;
	int base = a;
	while (n > 0)
	{
		if (n & 1)
		{
			ans = ans * (long long)base % mod;
		}
		base = (long long)base * base % mod;
		n >>= 1;
	}
	return ans;
}