#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <random>
#include <numeric>
#include <queue>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <stack>
#include <limits>
#include <climits>
#include <cassert>
#include <fstream>
#include <cstring>
#include <cmath>
#include <bitset>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <ciso646>
#include <set>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <type_traits>

using namespace std;

#define FOR(i,a,b) for (int i=(a);i<(b);i++)
#define RFOR(i,a,b) for (int i=(b)-1;i>=(a);i--)
#define REP(i,n) for (int i=0;i<(n);i++)
#define RREP(i,n) for (int i=(n)-1;i>=0;i--)
#define inf 0x3f3f3f3f3f3f3f3f
#define ALL(a) (a).begin(),(a).end()
#define DEBUG(x) cout<<#x<<": "<<x<<endl
#define ll long long
#define ull unsigned long long
using pii = pair<ll, ll>;
#define eps 1e-14
#define SETUP cin.tie(0), ios::sync_with_stdio(false), cout << setprecision(15) << std::fixed;

template <class T>
using vec2 = std::vector<vector<T>>;

namespace {
	struct input_returnner {
		ll N; input_returnner(ll N_ = 0) :N(N_) {}
		template<typename T> operator vector<T>() const { vector<T> res(N); for (auto &a : res) cin >> a; return std::move(res); }
		template<typename T> operator T() const { T res; cin >> res; return res; }
		template<typename T> T operator - (T right) { return T(input_returnner()) - right; }
		template<typename T> T operator + (T right) { return T(input_returnner()) + right; }
		template<typename T> T operator * (T right) { return T(input_returnner()) * right; }
		template<typename T> T operator / (T right) { return T(input_returnner()) / right; }
		template<typename T> T operator << (T right) { return T(input_returnner()) << right; }
		template<typename T> T operator >> (T right) { return T(input_returnner()) >> right; }
	};
	template<typename T> input_returnner in() { return in<T>(); }
	input_returnner in() { return input_returnner(); }
	input_returnner in(ll N) { return std::move(input_returnner(N)); }
}

template<typename T>
istream& operator >> (istream& is, vector<T>& vec) {
	for (T& x : vec) is >> x;
	return is;
}

template < typename T >
struct is_vector : std::false_type {};

template < typename T >
struct is_vector<std::vector<T>> : std::true_type {};

template < typename T >
constexpr bool is_vector_v = is_vector<T>::value;

template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
	if (!v.empty()) {
		for (int i = 0; i < v.size(); ++i) {
			out << v[i] << (i == v.size() - 1 ? "\n" : (is_vector_v<T> ? "" : ", "));
		}
	}
	return out;
}

namespace std {
	// ref: https://stackoverflow.com/questions/7110301/generic-hash-for-tuples-in-unordered-map-unordered-set
	template <class T>
	inline void hash_combine(std::size_t& seed, T const& v)
	{
		seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}

	// Recursive template code derived from Matthieu M.
	template <class Tuple, size_t Index = std::tuple_size<Tuple>::value - 1>
	struct HashValueImpl
	{
		static void apply(size_t& seed, Tuple const& tuple)
		{
			HashValueImpl<Tuple, Index - 1>::apply(seed, tuple);
			hash_combine(seed, std::get<Index>(tuple));
		}
	};

	template <class Tuple>
	struct HashValueImpl<Tuple, 0>
	{
		static void apply(size_t& seed, Tuple const& tuple)
		{
			hash_combine(seed, std::get<0>(tuple));
		}
	};
	template <typename ... TT>
	struct hash<std::tuple<TT...>>
	{
		size_t operator()(std::tuple<TT...> const& tt) const
		{
			size_t seed = 0;
			HashValueImpl<std::tuple<TT...> >::apply(seed, tt);
			return seed;
		}
	};

	template <class T, class U>
	class hash<std::pair<T, U>> {
	public:
		size_t operator()(const std::pair<T, U>& x) const {
			return hash<std::tuple<T, U>>()(std::tie(x.first, x.second));
		}
	};
}

// ref: https://stackoverflow.com/questions/6245735/pretty-print-stdtuple
namespace aux {
	template<std::size_t...> struct seq {};

	template<std::size_t N, std::size_t... Is>
	struct gen_seq : gen_seq<N - 1, N - 1, Is...> {};

	template<std::size_t... Is>
	struct gen_seq<0, Is...> : seq<Is...> {};

	template<class Ch, class Tr, class Tuple, std::size_t... Is>
	void print_tuple(std::basic_ostream<Ch, Tr>& os, Tuple const& t, seq<Is...>) {
		using swallow = int[];
		(void)swallow {
			0, (void(os << (Is == 0 ? "" : ", ") << std::get<Is>(t)), 0)...
		};
	}
} // aux::

template<class Ch, class Tr, class... Args>
auto operator<<(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& t)
-> std::basic_ostream<Ch, Tr>&
{
	os << "(";
	aux::print_tuple(os, t, aux::gen_seq<sizeof...(Args)>());
	return os << ")";
}

template<class S, class T>
std::ostream & operator<<(std::ostream & os, const std::pair<S, T> & p)
{
	return os << "(" << p.first << ", " << p.second << ")";
}

// ref: https://stackoverflow.com/questions/8542591/c11-reverse-range-based-for-loo�Fp
template <typename T>
struct reversion_wrapper { T& iterable; };

template <typename T>
auto begin(reversion_wrapper<T> w) { return std::rbegin(w.iterable); }

template <typename T>
auto end(reversion_wrapper<T> w) { return std::rend(w.iterable); }

template <typename T>
reversion_wrapper<T> REV(T&& iterable) { return { iterable }; }

template<class T>
bool inside(T left, T val, T right) {
	return left <= val and val < right;
}

int bitCount(int num) {
	int res = 0;
	while (num > 0) {
		num >>= 1;
		++res;
	}
	return res;
}

ll MOD = 1e9 + 7;

void solve();

signed main() {
	SETUP;
#ifdef _DEBUG
	while (true) {
#endif
		solve();
#ifdef _DEBUG
		cout << "-------" << endl;
	}
#endif
#ifdef _DEBUG
	system("pause");
#endif
	return 0;
}

// template

#define int ll

class prime {
private:
public:
	std::vector<int> primes;
	std::vector<bool> isPrime;
	prime(int num = 0) {
		if (num == 0) return;
		isPrime.resize(num + 1);
		fill(isPrime.begin(), isPrime.end(), true);
		int ma = sqrt(num) + 1;
		isPrime[0] = isPrime[1] = false;
		int cnt = 0;
		for (int i = 2; i <= ma; ++i) if (isPrime[i]) {
			for (int j = 2; i*j <= num; ++j) {
				isPrime[i*j] = false;
				cnt++;
			}
		}
		primes.reserve(cnt);
		for (int i = 0; i < isPrime.size(); ++i) if (isPrime[i]) {
			primes.push_back(i);
		}
	}

	bool IsPrime(int num) {
		if (num < isPrime.size()) return isPrime[num];
		for (auto p : primes) {
			if (num%p == 0) return false;
		}
		int ma = sqrt(num) + 1;
		for (int i = primes.back(); i <= ma; i += 2) {
			if (num%i == 0) return false;
		}
		return true;
	}

	std::map<int, int> GetFactor(int num) {
		std::map<int, int> res;
		int a = 2;
		auto it = primes.begin();
		while (num >= a * a) {
			if (num%a == 0) {
				res[a]++;
				num /= a;
			}
			else {
				++it;
				if (it == primes.end()) {
					break;
				}
				a = *it;
			}
		}
		res[num]++;
		return res;
	}
};

void solve() {
	int N, M, K; cin >> N >> M >> K;
	prime primes(sqrt(1e9) + 1);
	auto nfactors = primes.GetFactor(N);
	auto mfactors = primes.GetFactor(M);
	auto kfactors = primes.GetFactor(K);

	for (auto &a : kfactors) {
		int rest = a.second;
		auto& nf = nfactors[a.first];
		auto& mf = mfactors[a.first];
		while (rest > 0 and nf > 0) {
			nf--;
			--rest;
		}
		while (rest > 0 and mf > 0) {
			mf--;
			--rest;
		}
		if (rest > 0) {
			cout << "No" << endl;
			return;
		}
	}

	int x = 1;
	int y = 1;

	for (auto &a : nfactors) {
		REP(i, a.second) {
			x *= a.first;
		}
	}
	for (auto &a : mfactors) {
		REP(i, a.second) {
			y *= a.first;
		}
	}

	if (x * 2 < N) x *= 2;
	else if (y * 2 < N) y *= 2;
	else {
		cout << "NO" << endl;
		return;
	}

	cout << "YES" << endl;
	cout << "0 0" << endl;
	cout << x << " 0" << endl;
	cout << "0 " << y << endl;
}
