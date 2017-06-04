template <class T>
struct vector2 {
	T x;
	T y;
	vector2(T x_, T y_) :x(x_), y(y_) {}
	vector2() :x(0), y(0) {}
	vector2 operator + (const vector2<T>& right) { return vector2(x + right.x, y + right.y); }
	vector2 operator - (const vector2<T>& right) { return vector2(x - right.x, y - right.y); }
	T dot(const vector2<T>& right) { return x*right.x + y*right.y; }
	T det(const vector2<T>& right) { return (x*right.y) + (-y*right.x); }
};

