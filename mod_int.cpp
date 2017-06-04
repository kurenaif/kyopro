const ll mod = 1e9 + 7;

struct ModInt {
	ll v = 0;
	ModInt() {}
	template<class T> ModInt(const T& right) {
		v = right;
		if (v >= 0) v %= mod;
		else v += ((-v) / mod + 1)*mod;
		v %= mod;
	}
	void operator = (const ModInt& right) { v = right.v; }
	template<class T> void operator = (const T& right) {
		v = right;
		if (v >= 0) v %= mod;
		else v = v += ((-v) / mod + 1)*mod;
		v %= mod;
	}

	ModInt operator + (const ModInt& right) { return (v + right.v) % mod; }
	ModInt operator - (const ModInt& right) { return (mod - (v - right.v)); }
	ModInt operator * (const ModInt& right) { return (v * right.v) % mod; }

	void operator += (const ModInt& right) { v = (v + right.v) % mod; }
	void operator -= (const ModInt& right) { v = (mod - (v - right.v)); }
	void operator *= (const ModInt& right) { v = (v* right.v) % mod; }
};

ostream& operator << (ostream& os, const ModInt& value) {
	os << value.v;
	return os;
}
