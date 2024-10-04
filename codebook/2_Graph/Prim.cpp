auto prim = [&](int n, vector<vector<pair<int, int>>> &adj) -> bool {
    int sz = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, 0); // w, vertex
    vector<bool> vis(n);
    while (!pq.empty()) {
        auto [u, w] = pq.top();
        pq.pop();
        if (vis[u]) {
            continue;
        }
        vis[u] = true;
        sz++;
        for (auto v : adj[u]) {
            if (!vis[v.first]) {
                pq.emplace(v.second, v.first);
            }
        }
    }
    if (sz == n) {
        return true;
    }
    return false;
};