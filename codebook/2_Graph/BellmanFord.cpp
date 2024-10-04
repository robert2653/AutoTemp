// 用 Bellman Ford 找負環
int main() {
    int n, m;
    cin >> n >> m;
    vector<array<int, 3>> e;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        e.push_back({u, v, w});
    }
    vector<ll> dis(n, inf), par(n);
    int t = -1;
    dis[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (auto [u, v, w] : e) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                par[v] = u;
                if (i == n) t = v;
            }
        }
    }
    if (t == -1) {
        cout << "NO\n";
        return;
    }

    for (int i = 1; i < n; i++) {
        t = par[t];
    }
    vector<int> ans {t};
    int i = t;
    do {
        i = par[i];
        ans.push_back(i);
    } while (i != t);
    reverse(ans.begin(), ans.end());

    cout << "YES\n";
    for (auto x : ans) {
        cout << x + 1 << " ";
    }
}