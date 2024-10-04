template<class T>
pair<T, Point<T>> minCircle(vector<Point<T>> &a) {
    shuffle(a.begin(), a.end(), rng);
    int n = a.size();
    Point<T> c = a[0]; T r = 0;
    for (int i = 1; i < n; i++) {
        if (T(length(c - a[i]) - r) > 0.0) {
            c = a[i], r = 0;
            for (int j = 0; j < i; j++) {
                if (T(length(c - a[j]) - r) > 0.0) {
                    c = (a[i] + a[j]) / 2.0;
                    r = length(c - a[i]);
                    for (int k = 0; k < j; k++) {
                        if (T(length(c - a[k]) - r) > 0.0) {
                            Point<T> p = (a[j] + a[i]) / 2;
                            Point<T> q = (a[j] + a[k]) / 2;
                            if (cross(a[j] - a[i], a[k] - a[j]) == 0) {
                                continue;
                            }
                            c = lineIntersection(Line(p, p + rotate(a[j] - a[i])), Line(q, q + rotate(a[k] - a[j])));
                            r = length(c - a[i]);
                        }
                    }
                }
            }
        }
    }
    return {r, c};
}