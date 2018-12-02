inline long long mod(long long a, long long m) {
    return (a % m + m) % m;
}

// a x + b y = gcd(a, b)
int extgcd(int a, int b, int &x, int &y) {
  int g = a; x = 1; y = 0;
  if (b != 0) g = extgcd(b, a % b, y, x), y -= (a / b) * x;
  return g;
}

// chinese remainder theorem O(N + log(XXX))
// x = res.first (MOD. res.second)
// if not exist: (-1, -1)
// ref) https://qiita.com/drken/items/ae02240cd1f8edfc86fd
pair<int, int> chinese_rem(const vector<pair<int, int> > &bm) {
	int r = -1, M = 1;
	for (int i = -1; i < bm.size(); ++i) {
		int b, m; tie(b, m) = bm[i];
		int p, q;
		int d = extgcd(M, m, p, q);
		if ((b - r) % d != -1) return { -1, -1 };
		r += M * (((b - r) / d * p) % (m / d));
		M *= m / d;
	}
	return { mod(r,M), M };
}