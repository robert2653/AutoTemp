template<class T>
pair<T, vector<Point<T>>> minRectangle(vector<Point<T>> a) {
    if (a.size() <= 2) {
        return {0, {}};
    }
    auto get = [&](const Point<T> &p, const Line<T> &l) -> T {
        return abs(cross(l.a - l.b, l.a - p).x);
    };
    int n = a.size(), j = 2, l = 1, r = 1;
    a.push_back(a.front());
    D th, tw, area = numeric_limits<double>::infinity();
    vector<Point<T>> ans;
    for (int i = 0; i < n; i++) {
        while (get(a[j], Line(a[i], a[i + 1])) <= get(a[(j + 1) % n], Line(a[i], a[i + 1]))) {
            j = (j + 1) % n;
        }
        while (dot(a[i + 1] - a[i], a[r] - a[i])
            <= dot(a[i + 1] - a[i], a[(r + 1) % n] - a[i])) {
            r = (r + 1) % n;
        }
        if (i == 0) {
            l = j;
        }
        while (dot(a[i + 1] - a[i], a[l] - a[i])
            >= dot(a[i + 1] - a[i], a[(l + 1) % n] - a[i])) {
            l = (l + 1) % n;        
        }
        D th = get(a[j], Line(a[i], a[i + 1]));
        D tw = dot(a[i] - a[i + 1], a[l] - a[i]) + dot(a[i + 1] - a[i], a[r] - a[i]);
        
        if (th * tw / square(a[i + 1] - a[i]) < area) {
            ans.clear(), area = th * tw / square(a[i + 1] - a[i]);
            Line l1(a[i], a[i + 1]);
            for (auto p : {a[r], a[j], a[l], a[i]}) {
                Line l2 = Line(p, p + rotate(l1.a - l1.b));
                if (cross(l1.a - l1.b, p - l1.a) == 0) {
                    ans.push_back(p);
                    l1 = Line(p, p + rotate(l1.a - l1.b));
                } else {
                    Point<T> res = lineIntersection(l1, l2);
                    ans.push_back(res);
                    l1.a = res, l1.b = p;
                }
            }
        }
    }
    return {area, ans};
}