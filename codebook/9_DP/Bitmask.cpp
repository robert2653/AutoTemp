void hamiltonianPath() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[--v].push_back(--u);
    }
    // 以...為終點，走過...
    vector dp(n, vector<int>(1 << n));
    dp[0][1] = 1;
    for (int mask = 1; mask < 1 << n; mask++) {
        if ((mask & 1) == 0) {
            continue;
        }
        for (int i = 0; i < n; i++) {
            if ((mask >> i & 1) == 0) {
                continue;
            }
            if (i == n - 1 && mask != (1 << n) - 1) {
                continue;
            }
            int pre = mask ^ (1 << i);
            for (int j : adj[i]) {
                if ((pre >> j & 1) == 0) {
                    continue;
                }
                dp[i][mask] = (dp[i][mask] + dp[j][pre]) % Mod;
            }
        }
    }
    cout << dp[n - 1][(1 << n) - 1] << "\n";
}
void elevatorRides() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> dp(1 << n), f(1 << n);
    dp[0] = 1; // 次數、已使用人數
    for (int mask = 1; mask < 1 << n; mask++) {
        dp[mask] = 2E9;
        for (int i = 0; i < n; i++) {
            if ((mask >> i & 1) == 0) {
                continue;
            }
            int pre = mask ^ (1 << i);
            if (f[pre] + a[i] <= x) {
                if (dp[pre] < dp[mask] || dp[pre] == dp[mask] && f[pre] + a[i] < f[mask]) {
                    dp[mask] = dp[pre];
                    f[mask] = f[pre] + a[i];
                }
            } else if (dp[pre] + 1 < dp[mask] || dp[pre] + 1 == dp[mask] && a[i] < f[mask]) {
                dp[mask] = dp[pre] + 1;
                f[mask] = a[i];
            }
        }
    }
    cout << dp[(1 << n) - 1] << "\n";
}
void minClique() { // 移掉一些邊, 讓整張圖由最少團組成
    int n, m;
    cin >> n >> m;
    vector<bitset<N>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u][v] = g[v][u] = 1;
    }
    vector<int> dp(1 << n, inf);
    dp[0] = 1;
    for (int mask = 0; mask < 1 << n; mask++) { // 先正常 dp
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                int pre = mask ^ (1 << i);
                if (dp[pre] == 1 && (g[i] & bitset<N>(pre)) == pre) {
                    dp[mask] = 1; // i 有連到所有 pre
                }
            }
        }
    }
    for (int mask = 0; mask < 1 << n; mask++) { // 然後枚舉子集 dp
        for (int sub = mask; sub; --sub &= mask) {
            dp[mask] = min(dp[mask], dp[sub] + dp[mask ^ sub]);
        }
    }
    cout << dp[(1 << n) - 1] << "\n";
}