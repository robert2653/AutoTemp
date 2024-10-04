int main() {
    int n;
    vector<vector<int>> adj(n);
    // dfs_graph
    vector<bool> vis(n);
    auto dfs = [&](auto self, int u) -> void {
        if (vis[u]) {
            return;
        }
        vis[u] = true;
        for (auto v: adj[u]) {
            self(self, v);
        }
    };
    dfs(dfs, 0);
    // bfs
    vector<int> depth(n, 1E9);
    queue<int> q;
    auto bfs = [&](auto self, int s) -> void {
        vis[s] = true;
        depth[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto v : adj[u]) {
                if (vis[v]) continue;
                vis[v] = true;
                depth[v] = depth[u] + 1;
                q.push(v);
            }
        }
    };
    bfs(bfs, 0);
}