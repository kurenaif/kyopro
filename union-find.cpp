class union_find {
private:
	vector<int> par;
	vector<int> rank;
	vector<int> count;
public:
	union_find(int N) :par(N), rank(N, 0), count(N, 1) {
		for (int i = 0; i < N; ++i) {
			par[i] = i;
		}
	}

	int find(int x) {
		if (par[x] == x) {
			return x;
		}
		else {
			return par[x] = find(par[x]);
		}
	}

	void unite(int x, int y) {
		x = find(x);
		y = find(y);
		if (x == y) return;

		if (rank[x] < rank[y]) {
			count[y] += count[x];
			par[x] = y;
		}
		else {
			count[x] += count[y];
			par[y] = x;
			if (rank[x] == rank[y]) rank[x]++;
		}
	}

	bool same(int x, int y) {
		return find(x) == find(y);
	}

	int getCount(int x) {
		return count[find(x)];
	}

	void clean() {
		par = vector<int>(par.size());
	}
};
