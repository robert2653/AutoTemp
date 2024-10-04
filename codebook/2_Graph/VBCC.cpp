struct VBCC {
    int n, cur, cnt;
    vector<vector<int>> adj, bcc;
    vector<int> stk, dfn, low;
    vector<bool> ap;
    VBCC(int n_ = 0) { init(n_); }
    void init(int n_) {
        n = n_;
        adj.assign(n, {});
        dfn.assign(n, -1);
        low.resize(n);
        bcc.assign(n, {});
        ap.assign(n, false);
        stk.clear();
        cur = cnt = 0;
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void dfs(int x, int p) {
        dfn[x] = low[x] = cur++;
        stk.push_back(x);
        int ch = 0;
        for (auto y : adj[x]) {
            if (y == p) {
                continue;
            }
            if (dfn[y] == -1) {
                dfs(y, x);
                ch++;
                low[x] = min(low[x], low[y]);
                if (low[y] >= dfn[x]) {
                    int v;
                    do {
                        v = stk.back();
                        bcc[v].push_back(cnt);
                        stk.pop_back();
                    } while (v != y);
                    bcc[x].push_back(cnt);
                    cnt++;
                }
                if (low[y] >= dfn[x] && p != -1) {
                    ap[x] = true;
                }
            } else {
                low[x] = min(low[x], dfn[y]);
            }
        }
        if (p == -1 && ch > 1) {
            ap[x] = true;
        }
    }
    vector<bool> work() {
        for (int i = 0; i < n; i++) {
            if (dfn[i] == -1) {
                dfs(i, -1);
            }
        }
        return ap;
    }
    struct Graph {
        int n;
        vector<pair<int, int>> edges;
        vector<int> bel, siz, cnte;
    };
    Graph compress() {
        Graph g; // 壓完是一棵樹, 但不一定每個 bel 都有節點
        g.bel.resize(n);
        g.siz.resize(cnt);
        g.cnte.resize(cnt);
        for (int u = 0; u < n; u++) {
            if (ap[u]) {
                g.bel[u] = cnt++;
                g.siz.emplace_back();
                g.cnte.emplace_back();
                for (auto v : bcc[u]) {
                    g.edges.emplace_back(g.bel[u], v);
                }
            } else if (bcc[u].size() == 1) {
                g.bel[u] = bcc[u][0];
            }
            g.siz[g.bel[u]]++;
        }
        g.n = cnt;
        for (int i = 0; i < n; i++) {
            for (auto j : adj[i]) {
                if (g.bel[i] == g.bel[j] && i < j) {
                    g.cnte[g.bel[i]]++;
                }
            }
        }
        return g;
    }
};