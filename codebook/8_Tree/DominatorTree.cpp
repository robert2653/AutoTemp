// dom 存起點到達此點的必經的上個節點(起點 = 自己), 無法到達 = -1
struct Dominator_tree {
    int n, id;
    vector<vector<int>> adj, radj, bucket;
    vector<int> sdom, dom, vis, rev, pa, rt, mn, res;
    Dominator_tree(int n_ = 0) { init(n_); }
    void init(int n_) {
        n = n_, id = 0;
        adj.assign(n, {});
        radj.assign(n, {});
        bucket.assign(n, {});
        sdom.resize(n);
        dom.assign(n, -1);
        vis.assign(n, -1);
        rev.resize(n);
        pa.resize(n);
        rt.resize(n);
        mn.resize(n);
        res.resize(n);
    }
    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }
    int query(int v, int x) {
        if (rt[v] == v) {
            return x ? -1 : v;
        }
        int p = query(rt[v], 1);
        if (p == -1) {
            return x ? rt[v] : mn[v];
        }
        if (sdom[mn[v]] > sdom[mn[rt[v]]]) {
            mn[v] = mn[rt[v]];
        }
        rt[v] = p;
        return x ? p : mn[v];
    }
    void dfs(int v) {
        vis[v] = id, rev[id] = v;
        rt[id] = mn[id] = sdom[id] = id, id++;
        for (int u : adj[v]) {
            if (vis[u] == -1) {
                dfs(u), pa[vis[u]] = vis[v];
            }
            radj[vis[u]].push_back(vis[v]);
        }
    }
    vector<int> build(int s) {
        dfs(s);
        for (int i = id - 1; i >= 0; i--) {
            for (int u : radj[i]) {
                sdom[i] = min(sdom[i], sdom[query(u, 0)]);
            }
            if (i) {
                bucket[sdom[i]].push_back(i);
            }
            for (int u : bucket[i]) {
                int p = query(u, 0);
                dom[u] = sdom[p] == i ? i : p;
            }
            if (i) {
                rt[i] = pa[i];
            }
        }
        res.assign(n, -1);
        for (int i = 1; i < id; i++) {
            if (dom[i] != sdom[i]) {
                dom[i] = dom[dom[i]];
            }
        }
        for (int i = 1; i < id; i++) {
            res[rev[i]] = rev[dom[i]];
        }
        res[s] = s;
        for (int i = 0; i < n; i++) {
            dom[i] = res[i];
        }
        return dom;
    }
};