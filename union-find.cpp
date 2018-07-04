class UnionFind{
	vector<int> to;
	vector<int> cnt;
	vector<int> rank;

public:
	UnionFind(int N) {
		to = vector<int>(N); REP(i, N) to[i] = i;
		cnt = vector<int>(N, 1);
		rank = vector<int>(N, 1);
	}

	size_t size() {
		return to.size();
	}

	int root(int node) {
		if (node == to[node]) {
			return node;
		}
		to[node] = root(to[node]);
		return to[node];
	}

	int count(int node) {
		return cnt[root(node)];
	}

	int same(int a, int b) {
		return root(a) == root(b);
	}


	void unite(int a,int b){
		if (rank[a] < rank[b]) swap(a, b);
		int rootb = root(b), roota = root(a);
		to[rootb] = roota;
		cnt[roota] += cnt[rootb];
		if (rank[a] == rank[b]) ++rank[a];
	}
};
