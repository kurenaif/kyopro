struct BIT {
	vector<int> bit;
	int n;

	BIT(int N) :n(N+2), bit(N * 2){}

	int sum(int i) {
		++i;
		int s = 0;
		while (i > 0) {
			s += bit[i];
			i -= i&-i;
		}
		return s;
	}

	void add(int i, int x) {
		++i;
		while (i <= n) {
			bit[i] += x;
			i += i & (-i);
		}
	}
};
