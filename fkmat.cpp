template<class T>
struct fkvector {
public:
	vector<T> v;
	fkvector(size_t size) :v(size) {}
	size_t size() const { return v.size(); }

	T& operator [] (const int index) {
		return v[index];
	}

	T dot(const fkvector<T>& right) {
		assert(v.size() == right.size());
		T res = 0;
		for (int i = 0; i < right.size(); ++i) {
			res += v[i] * right.v[i];
		}
		return res;
	}

	void operator = (const fkvector<T>& right) {
		v.clear();
		v.resize(right.size());
		copy(right.v.begin(), right.v.end(), v.begin());
	}

	fkvector<T> operator + (const fkvector<T>& right) {
		assert(v.size() == right.size());
		fkvector<T> res(v.size());
		for (size_t i = 0; i < v.size(); ++i) {
			res[i] = v[i] + right.v[i];
		}
		return res;
	}

	fkvector<T> operator - (const fkvector<T>& right) {
		assert(v.size() == right.size());
		fkvector<T> res(v.size());
		for (size_t i = 0; i < v.size(); ++i) {
			res[i] = v[i] - right.v[i];
		}
		return res;
	}

	void operator += (const fkvector<T>& right) {
		assert(v.size() == right.size());
		*this = *this + right;
	}

	void operator -= (const fkvector<T>& right) {
		assert(v.size() == right.size());
		*this = *this - right;
	}

	void print() {
		cout << "{";
		for (int i = 0; i < v.size()-1; ++i) {
			cout << v[i] << ", ";
		}
		cout << v.back();
		cout << "}" << endl;
	}
};

template<class T>
struct fkmat {
	vector<vector<T> > mat;

	size_t getRowCount() const { return mat.size(); }
	size_t getColomnCount() const { return mat[0].size(); }
	size_t size() const { return mat.size(); }

	fkmat(size_t size_row,size_t size_colomn):mat(size_row, vector<T>(size_colomn)) {}

	vector<T>& operator [] (const int index) { return mat[index]; }

	//Identity matrix
	fkmat<T> Identity() {
		for (int i = 0; i < mat.size(); ++i) {
			mat[i][i] = 1;
		}
		return *this;
	}

	void operator = (const fkmat<T>& right) {
		mat.clear();
		mat.resize(right.size());
		for (int i = 0; i < right.size(); ++i) {
			mat[i] = right.mat[i];
		}
	}

	fkmat<T> operator + (const fkmat<T>& right) {
		fkmat<T> res(getRowCount(), getColomnCount());

		for (int i = 0; i < mat.size(); ++i) {
			for (int j = 0; j < mat[i].size(); ++j) {
				res[i][j] = mat[i][j] + right.mat[i][j];
			}
		}
		
		return res;
	}

	fkmat<T> operator - (const fkmat<T>& right) {
		fkmat<T> res(getRowCount(), getColomnCount());

		for (int i = 0; i < mat.size(); ++i) {
			for (int j = 0; j < mat[i].size(); ++j) {
				res[i][j] = mat[i][j] - right.mat[i][j];
			}
		}
		
		return res;
	}

	fkmat<T> operator * (const fkmat<T>& right) {
		fkmat<T> res(getRowCount(), getColomnCount());
		assert(getRowCount() == right.getColomnCount());

		for (int r = 0; r < getRowCount(); ++r) {
			for (int c = 0; c < right.getColomnCount(); ++c) {
				for (int k = 0; k < getColomnCount(); ++k) {
					res[r][c] += mat[r][k] * right.mat[k][c];
				}
			}
		}

		return res;
	}

	void operator += (const fkmat<T>& right) {
		for (int i = 0; i < mat.size(); ++i) {
			for (int j = 0; j < mat[i].size(); ++j) {
				mat[i][j] += right.mat[i][j];
			}
		}
	}
	
	void operator -= (const fkmat<T>& right) {
		for (int i = 0; i < mat.size(); ++i) {
			for (int j = 0; j < mat[i].size(); ++j) {
				mat[i][j] -= right.mat[i][j];
			}
		}
	}

	void operator *= (const fkmat<T>& right) {
		*this = *this * right;
	}

	//power n
	void pow(long long n, fkmat<T>* dst) {
		dst->Identity();
		fkmat<T> x(getRowCount(), getColomnCount());
		x.mat = mat;
		while (n > 0) {
			if (n & 1) *dst = *dst * x;
			x *= x;
			n >>= 1;
		}
	}

	//power n
	void pow(long long n) {
		fkmat<T> res = mat(getRowCount(), getColomnCount());
		res = mat;
		fkmat<T> x;
		x = mat(getRowCount(), getColomnCount());
		while (n > 0) {
			if (n & 1) res = res * x;
			x *= x;
			n >>= 1;
		}
		mat = res;
	}

	void print() {
		for (size_t i = 0; i < mat.size(); ++i) {
			for (size_t j = 0; j < mat[i].size(); ++j) {
				cout << mat[i][j] << " ";
			}
			cout << endl;
		}
	}
};

int main(void) {
	fkmat<int> m(3, 3);

	for (int i = 0; i < m.size(); ++i) {
		for (int j = 0; j < m[i].size(); ++j) {
			m[i][j] = i;
		}
	}

	m.print(); cout << endl;

	fkmat<int> dst(3, 3);

	m.pow(10, &dst);

	dst.print();

	return 0;
}
