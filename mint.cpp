struct mint {
	int64_t value;
	mint():value(0){}
	mint(int64_t value_) : value(value_%MOD) {}
	inline mint& operator += (const mint& rhs) {
		value += rhs.value;
		if (value >= MOD) { value -= MOD; }
		return *this;
	}
	inline mint& operator -= (const mint& rhs) {
		value -= rhs.value;
		if (value < 0) {
			value += MOD;
		}
		return *this;
	}
	inline mint& operator *= (const mint& rhs) {
		value *= rhs.value;
		value %= MOD;
		return *this;
	}
	inline mint& operator %= (const mint& rhs) {
		return *this;
	}
};

inline mint operator + (const mint& lhs, const mint& rhs) { mint res = lhs; res += rhs; return res; }
inline mint operator - (const mint& lhs, const mint& rhs) { mint res = lhs;	res -= rhs;	return res; }
inline mint operator * (const mint& lhs, const mint& rhs) { mint res = lhs;	res *= rhs;	return res; }
inline mint operator % (const mint& lhs, const uint64_t& rhs) { return lhs; }

ostream & operator << (ostream & out, mint n) { return out << n.value; }

// x^n % mod
// O(log n)
mint mod_pow(mint x, uint64_t n) {
	mint res = 1;
	while (n > 0) {
		if (n & 1) res = res * x;
		x = x*x;
		n >>= 1;
	}
	return res;
}
