// CSES Police Chase
int main(){
    int n, m; cin >> n >> m;
    Dinic<int> g(n);
    for (int i = 0; i < m; i++) {
        int u, v, cap = 1;
        cin >> u >> v;
        u--; v--;
        g.add_edge(u, v, cap);
        g.add_edge(v, u, cap);
    }
    int res = g.work(0, n - 1);
    cout << res << "\n";
    if (res == 0) {
        return;
    }

    vector<int> vis(n);
    auto find = [&](auto self, int u) -> void {
        if (!vis[u]) {
            vis[u] = 1;
            for (int id : g.adj[u]) {
                auto e = g.edges[id];
                if (e.cap - e.flow > 0) {
                    self(self, e.to);
                }
            }
        }
    };
    find(find, 0);
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            continue;
        }
        for (int id : g.adj[i]) {
            if (id & 1) {
                continue;
            }
            auto e = g.edges[id];
            if (!vis[e.to]) {
                cout << i + 1 << " " << e.to + 1 << "\n";
            }
        }
    }
}