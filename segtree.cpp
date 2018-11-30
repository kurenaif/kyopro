template<class T>
class segtree {
private:
	int n;
	vector<T> dat;

	T query(int a, int b, int k, int l, int r) {
		if (r <= a || b <= l) return numeric_limits<T>::max();

		if (a <= l & r <= b) return dat[k];

		T vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
		T vr = query(a, b, k * 2 + 2, (l + r) / 2, r);

		return min(vl, vr);
	}
public:
	segtree(int n_) {
		n = 1;
		while (n < n_) n *= 2;
		dat.resize(2 * n - 1);
		for (int i = 0; i < 2 * n - 1; ++i) dat[i] = numeric_limits<T>::max();
	}

	//k‚Ì’l‚ğa‚É•ÏX
	void update(int k, int a) {
		k += n - 1;
		dat[k] = a;
		while (k > 0) {
			k = (k - 1) / 2;
			dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
		}
	}


	int query(int a, int b) {
		return query(a, b, 0, 0, n);
	}
};

