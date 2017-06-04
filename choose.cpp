// fact(n)%MOD, invFact(n)%MOD, inv(n)%MOD, nCk
// Constructor O(N)
// other O(1)
template<typename T, int MOD>
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

