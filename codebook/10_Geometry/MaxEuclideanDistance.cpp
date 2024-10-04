template<class T>
tuple<T, int, int> mxdisPair(vector<Point<T>> a) {
    auto get = [&](const Point<T> &p, const Line<T> &l) -> T {
        return abs(cross(l.a - l.b, l.a - p));
    };
    T res = 0;
    int n = a.size(), x, y, id = 2;
    a.push_back(a.front());
    if (n <= 2) {
        return {square(a[0] - a[1]), 0, 1};
    }
    for (int i = 0; i < n; i++) {
        while (get(a[id], Line(a[i], a[i + 1])) <= get(a[(id + 1) % n], Line(a[i], a[i + 1]))) {
            id = (id + 1) % n;
        }
        if (res < square(a[i] - a[id])) {
            res = square(a[i] - a[id]);
            x = i, y = id;
        }
        if (res < square(a[i + 1] - a[id])) {
            res = square(a[i + 1] - a[id]);
            x = i + 1, y = id;
        }
    }
    return {res, x, y};
}