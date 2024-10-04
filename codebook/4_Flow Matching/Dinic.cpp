template<class T>
struct Dinic {
    struct Edge {
        int to;
        T flow, cap; // 流量跟容量
    };
    int n, m, s, t;
    const T INF_FlOW = 1 << 30;
    vector<vector<int>> adj; // 此點對應的 edges 編號
    vector<Edge> edges; // 幫每個 edge 編號
    vector<int> dis, ptr;
    Dinic(int n_ = 0) {
        init(n_);
    }
    void init(int n_) {
        n = n_; m = 0;
        dis.resize(n);
        ptr.resize(n);
        adj.assign(n, {});
        edges.clear();
    }
    void add_edge(int u, int v, T cap) {
        edges.push_back({v, 0, cap});
        edges.push_back({u, 0, 0});
        adj[u].push_back(m++);
        adj[v].push_back(m++);
    }
    bool bfs() {
        fill(dis.begin(), dis.end(), -1);
        dis[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty() && dis[t] == -1) {
            int u = q.front(); q.pop();
            for (int id : adj[u]) {
                Edge &e = edges[id];
                if (e.flow == e.cap) {
                    continue;
                }
                if (dis[e.to] == -1) {
                    dis[e.to] = dis[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return dis[t] != -1;
    }
    T dfs(int u, T flow) {
        if (flow == 0) {
            return 0;
        }
        if (u == t) {
            return flow;
        }
        for (int &cur = ptr[u]; cur < adj[u].size(); cur++) {
            Edge &e = edges[adj[u][cur]];
            if (dis[u] + 1 != dis[e.to]) {
                continue;
            }
            if (e.cap == e.flow) {
                continue;
            }
            T mn = dfs(e.to, min(flow, e.cap - e.flow));
            if (mn > 0) {
                e.flow += mn;
                edges[adj[u][cur] ^ 1].flow -= mn;
                return mn;
            }
        }
        return 0;   // 到不了終點就會 return 0
    }
    T work(int s_, int t_) {
        s = s_;
        t = t_;
        T flow = 0;
        while (bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            while (true) {
                T res = dfs(s, INF_FlOW);
                if (res == 0) {
                    break;
                }
                flow += res;
            }
        }
        return flow;
    }
    void reset() {
        for (int i = 0; i < m; i++) {
            edges[i].flow = 0;
        }
    }
    void reuse(int n_) { // 走殘留網路, res += flow
        while (n < n_) {
            adj.emplace_back();
            dis.emplace_back();
            ptr.emplace_back();
            n += 1;
        }
    }
};