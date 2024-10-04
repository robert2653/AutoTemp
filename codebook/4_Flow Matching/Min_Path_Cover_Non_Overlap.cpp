// https://vjudge.net/problem/POJ-2594
#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

struct Hungarian { // 0-based
    int n, m; // 最小路徑覆蓋，二分匹配
    vector<vector<int>> adj;
    vector<int> used, vis;
    vector<pair<int, int>> match;
    Hungarian(int n_ = 0, int m_ = 0) {
        init(n_, m_);
    }
    void init(int n_, int m_) {
        n = n_; m = m_;
        adj.assign(n + m, vector<int>());
        used.assign(n + m, -1);
        vis.assign(n + m, 0);
    }
    void addEdge(int u, int v) {
        adj[u].push_back(n + v);
        adj[n + v].push_back(u);
    }
    bool dfs(int u) {
        int sz = adj[u].size();
        for (int i = 0; i < sz; i++) {
            int v = adj[u][i];
            if (vis[v] == 0) {
                vis[v] = 1;
                if (used[v] == -1 || dfs(used[v])) {
                    used[v] = u;
                    return true;
                }
            }
        }
        return false;
    }
    vector<pair<int, int>> work() {
        match.clear();
        used.assign(n + m, -1);
        vis.assign(n + m, 0);
        for (int i = 0; i < n; i++) {
            fill(vis.begin(), vis.end(), 0);
            dfs(i);
        }
        for (int i = n; i < n + m; i++) {
            if (used[i] != -1) {
                match.push_back(make_pair(used[i], i - n));
            }
        }
        return match;
    }
};

const int N = 500;
void Floyd(int n, vector<bitset<N>> &dp) {
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            if (dp[i][k])
                dp[i] |= dp[k]; 
}

void solve(int n, int m) {
    Hungarian g(n, n);

    vector<bitset<N>> dp(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        dp[u][v] = 1;
    }
    Floyd(n, dp);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dp[i][j]) {
                g.addEdge(i, j);
            }
        }
    }
    cout << n - g.work().size() << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    int n, m;
    // cin >> t;
    while (cin >> n >> m) {
        if (n || m) {
            solve(n, m);
        }
    }
}