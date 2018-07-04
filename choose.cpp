// fact(n)%MOD, invFact(n)%MOD, inv(n)%MOD, nCk
// Constructor O(N)
// other O(1)
template<typename T>
class Choose {
public:
	vector<T> fact, inv, invFact;
 
	Choose(T N):fact(N), inv(N), invFact(N){
		inv[1] = 1;
		FOR(i, 2, inv.size()) inv[i] = MOD - (MOD / i) * inv[MOD%i] % MOD;
		fact[0] = invFact[0] = 1;
		FOR(i, 1, fact.size()) {
			fact[i] = fact[i - 1] * i % MOD;
			invFact[i] = (invFact[i - 1] * inv[i]) % MOD;
		}
	}
 
	//Get nCk
	T operator () (T n, T k) const {
		if (not ((T)0 <= k and k <= n)) return 0;
		return (((fact[n] * invFact[k]) % MOD)*invFact[n - k]) % MOD;
	}
};

// binomial coefficients O(n^2)
// res[i][j] = C(i,j) (i , j <= n)
// C(i,j) =  C(i-1, j-1) + C(i-1, j)
// usage: 	vector<vector<int> > b = BinomialCoefficients(10);
vector<vector<int> > BinomialCoefficients(int n) {
	vector<vector<int > > res;
	res.resize(max(n+1,2LL));
	res[0].push_back(1);
	res[1].push_back(1);
	res[1].push_back(1);

	FOR(i, 2, res.size()){
		res[i].push_back(1);
		FOR(j,1,i){
			res[i].push_back((res[i - 1][j - 1] + res[i - 1][j])%MOD);
		}
		res[i].push_back(1);
	}
	return res;
}

// Stirling NUmber of The Second Kind O(n^2)
// note: NOT symmetry!!!
// S(n, k) = S(n, k-1) + k*S(n-1, k)
// usage: 	vector<vector<int> > s2 = StirlingNumber2(10);
vector<vector<int> > StirlingNumber2(int n) {
	vector<vector<int > > res;
	res.resize(max(n+1,2LL));
	res[0].push_back(1);
	res[1].push_back(0);
	res[1].push_back(1);

	FOR(i, 2, res.size()) {
		res[i].push_back(0);
		FOR(j,1,i){
			res[i].push_back((res[i-1][j - 1] + j*res[i-1][j]) % MOD);
		}
		res[i].push_back(1);
	}
	return res;
}
