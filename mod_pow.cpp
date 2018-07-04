// x^n % mod
// O(log n)
template<typename T>
T mod_pow(T x, T n, T mod) {
	T res = 1;
	while (n > 0) {
		if (n & 1) res = res * x % mod;
		x = x*x %mod;
		n >>= 1;
	}
	return res;
}
