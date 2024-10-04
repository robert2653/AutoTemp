void solve() {
    int n;
    cin >> n;
    constexpr ll inf = 8E18;
    vector<Point<ll>> a(n);
    for (int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        a[i] = Point<ll>(x, y);
    }
    struct sortY {
        bool operator()(const Point<ll> &a, const Point<ll> &b) const {
            return a.y < b.y;
        }
    };
    struct sortXY {
        bool operator()(const Point<ll> &a, const Point<ll> &b) const {
            return a.x == b.x ? a.y < b.y : a.x < b.x;
        }
    };
    sort(a.begin(), a.end(), sortXY());
    vector<Point<ll>> t(n);
    auto devide = [&](auto &&self, int l, int r) -> ll {
        if (l == r) {
            return inf;
        }
        int m = (l + r) / 2;	
        ll ans = min(self(self, l, m), self(self, m + 1, r));
        ll midval = a[m].x;
        ll p = 0;
        for (int i = l; i <= r; i++) {
            if ((midval - a[i].x) * (midval - a[i].x) <= ans) {
                t[p++] = a[i];
            }
        }
        sort(t.begin(), t.begin() + p, sortY());
        for (int i = 0; i < p; i++){
            for (int j = i + 1; j < p; j++) {
                ans = min(ans, square(t[i] - t[j]));
                if ((t[i].y - t[j].y) * (t[i].y - t[j].y) > ans) {
                    break;
                }
            } 
        }
        return ans;
    };
    cout << devide(devide, 0, n - 1) << "\n";
}