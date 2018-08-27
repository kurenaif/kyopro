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
		assert(getColomnCount() == right.getRowCount());

		for (int r = 0; r < getRowCount(); ++r) {
			for (int c = 0; c < right.getColomnCount(); ++c) {
				for (int k = 0; k < getColomnCount(); ++k) {
					res[r][c] += mat[r][k] * right.mat[k][c];
					res[r][c] %= MOD;
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
			x %= MOD;
			n >>= 1;
		}
	}

	//power n
	void pow(long long n) {
		fkmat<T> res(getRowCount(), getColomnCount());
		res = fkmat<T>(getRowCount(), getColomnCount()).Identity();
		fkmat<T> x(getRowCount(), getColomnCount());
		x = *this;
		while (n > 0) {
			if (n & 1) res = res * x;
			x *= x;
			n >>= 1;
		}
		*this = res;
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
