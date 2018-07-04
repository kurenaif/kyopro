struct Node {
	int company;
	int pos;
	Node(int company, int pos) :company(company), pos(pos) {}
	Node() {}
	bool operator == (const Node& rhs) {
		return company == rhs.company and pos == rhs.pos;
	}
};

namespace std{
    template<>
    class hash<Node>{
        public:
			size_t operator () (const Node &n) const {
				auto t = make_tuple(n.company, n.pos);
				return std::hash<decltype(t)>()(t);
			}
	};
}
