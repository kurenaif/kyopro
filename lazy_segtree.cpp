template<class T>
class LazySegtree {
private:
	int n;
	vector<T> dat;
	vector<T> lazy;
	vector<bool> lazyFlag;

	void eval(int k, int l, int r){
		if (lazyFlag[k]) {
			dat[k] = lazy[k];

			if (r - l > 1) {
				lazy[2 * k + 1] = lazy[k];
				lazy[2 * k + 2] = lazy[k];
				lazyFlag[2 * k + 1] = lazyFlag[2 * k + 2] = true;
			}
		}

		lazyFlag[k] = false;
	}

	T query(int a, int b, int k, int l, int r) {
		eval(k, l, r);
		if (r <= a || b <= l) return numeric_limits<T>::max();

		if (a <= l & r <= b) return dat[k];

		T vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
		T vr = query(a, b, k * 2 + 2, (l + r) / 2, r);

		return min(vl, vr);
	}

	// change [a,b) to value
	void update(int a, int b, T value, int k, int l, int r){
		eval(k, l, r);
		if (b <= l or r <= a) return;

		if (a <= l and r <= b) {
			lazy[k] = value;
			lazyFlag[k] = true;
			eval(k, l, r);
		}
		else {
			update(a, b, value, 2 * k + 1, l, (l + r) / 2);
			update(a, b, value, 2 * k + 2, (l + r) / 2, r);
			dat[k] = min(dat[2 * k + 1], dat[2 * k + 2]);
		}
	}
public:
	LazySegtree(int n_) {
		n = 1;
		while (n < n_) n *= 2;
		dat.resize(2 * n - 1);
		lazy.resize(2 * n - 1);
		lazyFlag.resize(2 * n - 1);
		for (int i = 0; i < 2 * n - 1; ++i) dat[i] = numeric_limits<T>::max();
	}


	// change [a,b] to value
	void update(int a, int b, T value){
		update(a, b, value, 0, 0, n);
	}

	// change k to value
	void update(int k, T value) {
		update(k, k + 1, value);
	}

	// get min value at [a, b)
	T query(int a, int b) {
		return query(a, b, 0, 0, n);
	}
};
