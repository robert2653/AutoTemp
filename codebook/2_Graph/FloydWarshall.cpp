constexpr ll inf = 1E18;
void FloydWarshall(int n, int m) {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> dis(n, vector<int>(n, inf));
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        dis[u][v] = min(dis[u][v], w);
        dis[v][u] = min(dis[v][u], w);
    }
    for (int i = 0; i < n; i++) {
        dis[i][i] = 0;
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
}

const int N = 500; // Floyd 封包
void Floyd(int n, vector<bitset<N>> &dp) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (dp[i][k]) {
                dp[i] |= dp[k]; 
            }
        }
    }
}