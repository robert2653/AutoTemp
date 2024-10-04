int main() {
    // Area 求法與 Polygun 內整數點數
    int n;
    cin >> n;
    vector<Point<ll>> polygon(n);
    for (int i = 0; i < n; i++) {
        cin >> polygon[i];
    }
    ll area = 0;
    for (int i = 0; i < n; i++) {
        area += cross(polygon[i], polygon[(i + 1) % n]);
    }
    area = abs(area);
    auto countBoundaryPoints = [](const vector<Point<ll>>& polygon) -> ll {
        ll res = 0;
        int n = polygon.size();
        for (int i = 0; i < n; i++) {
            ll dx = polygon[(i + 1) % n].x - polygon[i].x;
            ll dy = polygon[(i + 1) % n].y - polygon[i].y;
            res += std::gcd(abs(dx), abs(dy));
        }
        return res;
    };
    ll res = countBoundaryPoints(polygon);
    ll ans = (area - res + 2) / 2;
    cout << ans << " " << res << "\n";
}