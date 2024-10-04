// 多次詢問給某些關鍵點, 虛樹可達成快速樹 DP (前處理每個點)
// 例如這題是有權樹，給一些關鍵點, 求跟 vertex 1 隔開的最小成本
// 前處理 root 到所有點的最小邊權
vector<int> stk;
void insert(int key, vector<vector<int>> &vt) {
    if (stk.empty()) {
        stk.push_back(key);
        return;
    }
    int l = lca(stk.back(), key);
    if (l == stk.back()) {
        stk.push_back(key);
        return;
    }
    while (stk.size() > 1 && dfn[stk[stk.size() - 2]] > dfn[l]) {
        vt[stk[stk.size() - 2]].push_back(stk.back());
        stk.pop_back();
    }
    if (stk.size() < 2 || stk[stk.size() - 2] != l) {
        vt[l].push_back(stk.back());
        stk.back() = l;
    } else {
        vt[l].push_back(stk.back());
        stk.pop_back();
    }
    stk.push_back(key);
}
int work(vector<vector<int>> &vt) {
    while (stk.size() > 1) {
        vt[stk[stk.size() - 2]].push_back(stk.back());
        stk.pop_back();
    }
    int rt = stk[0];
    stk.clear();
    return rt;
}
void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    vector<vector<pair<int, int>>> wg(n);
    vector<vector<int>> vt(n);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
        wg[u].emplace_back(v, w);
        wg[v].emplace_back(u, w);
    }
    build(n, g); // build LCA
    vector<int> dis(n, 1E9); // root 到各點的最小邊權
    auto dfs_dis = [&](auto &&self, int x, int p) -> void {
        for (auto [y, w] : wg[x]) {
            if (y == p) {
                continue;
            }
            dis[y] = min(w, dis[x]);
            self(self, y, x);
        }
    };
    dfs_dis(dfs_dis, 0, -1);

    vector<bool> iskey(n);
    vector<ll> dp(n);
    int q;
    cin >> q;
    while (q--) {
        int m;
        cin >> m;
        vector<int> key(m);
        for (int i = 0; i < m; i++) {
            cin >> key[i];
            key[i] -= 1;
            iskey[key[i]] = true;
        }
        key.push_back(0); // 固定 0 為 root, 看題目需求
        sort(key.begin(), key.end(), [&](int a, int b) {
            return dfn[a] < dfn[b];
        }); // 要 sort 再 insert
        for (auto x : key) {
            insert(x, vt);
        }
        work(vt);
        auto dfs = [&](auto &&self, int x) -> void {
            for (auto y : vt[x]) {
                self(self, y);
                if (iskey[y]) { // 直接砍了
                    dp[x] += dis[y];
                } else { // 不砍 or 砍
                    dp[x] += min<ll>(dp[y], dis[y]);
                } // 記得 reset
                iskey[y] = dp[y] = 0;
            }
            vt[x].clear(); // 記得 reset
        };
        dfs(dfs, 0);
        cout << dp[0] << "\n";
        dp[0] = 0; // 最後 reset root
    }
}