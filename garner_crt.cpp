int gcd(int a, int b) {
	return b != 0 ? gcd(b, a % b) : a;
}

// a x + b y = gcd(a, b)
int extgcd(int a, int b, int &x, int &y) {
  int g = a; x = 1; y = 0;
  if (b != 0) g = extgcd(b, a % b, y, x), y -= (a / b) * x;
  return g;
}

inline long long mod(long long a, long long m) {
    return (a % m + m) % m;
}

// condition: gcd(a,m) == 1
long long modinv(long long a, long long m) {
    long long x, y;
    extgcd(a, m, x, y);
    return mod(x, m);
}

// preprocess for garner's algorithm O(N^2)
// gcd(b[]) != 0 => gcd(b[]) == 0
// res: lcm(b[]) % MOD
// out: bm
int pre_garner(vector<pair<int, int> > &bm, int MOD) {
	int res = 1;
	REP(i, bm.size()) {
		REP(j, i) {
			int& mi = bm[i].second;
			int& mj = bm[j].second;
			int& bi = bm[i].first;
			int& bj = bm[j].first;

			// common factor (smaller factors)
			int g = gcd(mi, mj);
			// Requirements
			if ((bi - bj) % g != 0) return -1;

			// remove smaller factor
			mi /= g, mj /= g;

			int gi = gcd(mi, g);
			int gj = g / gi;

			{
				int gg;
				do {
					gg = gcd(gi, gj);
					gi *= gg;
					gj /= gg;
				} while (gg != 1);
			}

			mi *= gi, mj *= gj;

			bi %= mi, bj %= mj;
		}
	}
	for (auto &a : bm) (res *= a.second) %= MOD;
	return res;
}

// garner's Algorithm O(N^2)
// for each step, we solve "coeffs[k] * t[k] + constants[k] = b[k] (mod. m[k])"
//      coeffs[k] = m[0]m[1]...m[k-1]
//      constants[k] = t[0] + t[1]m[0] + ... + t[k-1]m[0]m[1]...m[k-2]
// ref) https://qiita.com/drken/items/ae02240cd1f8edfc86fd
// res: {x % MOD, lcm % MOD}
pair<int, int> garner(vector<pair<int, int> > bm, int MOD) {
	int lcm = pre_garner(bm, MOD); // if gcd(m[]) != 0, need preprocess
	bm.emplace_back(-1, MOD); // banpei
	vector<int> coeffs(bm.size(), 1);
	vector<int> constants(bm.size(), 0);
	REP(k, bm.size()) {
		int& bk = bm[k].first;
		int& mk = bm[k].second;
		int t = mod((bk - constants[k]) * modinv(coeffs[k], mk), mk);
		FOR(i, k + 1, bm.size()) {
			int& mi = bm[i].second;
			(constants[i] += t * coeffs[i]) %= mi;
			(coeffs[i] *= mk) %= mi;
		}
	}
	return { constants.back(), lcm };
}
