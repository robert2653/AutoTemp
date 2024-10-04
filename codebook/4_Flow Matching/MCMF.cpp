template<class Tf, class Tc>
struct MCMF {
    struct Edge {
        int to;
        Tf flow, cap; // 流量跟容量
        Tc cost;
    };
    int n, m, s, t;
    const Tf INF_FLOW = 1 << 30;
    const Tc INF_COST = 1 << 30;

    vector<vector<int>> adj;
    vector<Edge> edges; // 幫每個 edge 編號
    vector<Tc> dis, pot; // johnson algorithm, using spfa
    vector<int> rt; // 路徑恢復，對應 id
    vector<bool> inq;

    MCMF(int n_ = 0) { init(n_); }
    void init(int n_) {
        n = n_;
        m = 0;
        edges.clear();
        adj.assign(n, {});
    }
    void add_edge(int u, int v, Tf cap, Tc cost) {
        edges.push_back({v, 0, cap, cost});
        edges.push_back({u, 0, 0, -cost});
        adj[u].push_back(m++);
        adj[v].push_back(m++);
    }
    bool spfa() {
        dis.assign(n, INF_COST);
        rt.assign(n, -1);
        inq.assign(n, false);
        queue<int> q;

        q.push(s);
        dis[s] = 0;
        inq[s] = true;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            inq[u] = false;
            for (int id : adj[u]) {
                auto [v, flow, cap, cost] = edges[id];
                Tc ndis = dis[u] + cost + pot[u] - pot[v];
                if (flow < cap && dis[v] > ndis) {
                    dis[v] = ndis;
                    rt[v] = id;
                    if (!inq[v]) {
                        q.push(v);
                        inq[v] = true;
                    }
                }
            }
        }
        return dis[t] != INF_COST;
    }
    bool dijkstra() {
        dis.assign(n, INF_COST);
        rt.assign(n, -1);
        priority_queue<pair<Tc, int>, vector<pair<Tc, int>>, greater<pair<Tc, int>>> pq;
        dis[s] = 0;
        pq.emplace(dis[s], s);
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (dis[u] < d) {
                continue;
            }
            for (int id : adj[u]) {
                auto [v, flow, cap, cost] = edges[id];
                Tc ndis = dis[u] + cost + pot[u] - pot[v];
                if (flow < cap && dis[v] > ndis) {
                    dis[v] = ndis; rt[v] = id;
                    pq.emplace(ndis, v);
                }
            }
        }
        return dis[t] != INF_COST;
    }
    // 限定 flow, 最小化 cost
    pair<Tf, Tc> work_flow(int s_, int t_, Tf need) {
        s = s_;
        t = t_;
        pot.assign(n, 0);
        Tf flow{};
        Tc cost{};
        bool fr = true;
        while ((fr ? spfa() : dijkstra())) {
            for (int i = 0; i < n; i++) {
                dis[i] += pot[i] - pot[s];
            }
            Tf f = INF_FLOW;
            for (int i = t; i != s; i = edges[rt[i] ^ 1].to) {
                f = min(f, edges[rt[i]].cap - edges[rt[i]].flow);
            }
            f = min<Tf>(f, need);
            for (int i = t; i != s; i = edges[rt[i] ^ 1].to) {
                edges[rt[i]].flow += f;
                edges[rt[i] ^ 1].flow -= f;
            }
            flow += f;
            need -= f;
            cost += f * dis[t];
            fr = false;
            swap(dis, pot);
            if (need == 0) {
                break;
            }
        }
        return {flow, cost};
    }
    // 限定 cost, 最大化 flow
    pair<Tf, Tc> work_budget(int s_, int t_, Tc budget) {
        s = s_;
        t = t_;
        pot.assign(n, 0);
        Tf flow{};
        Tc cost{};
        bool fr = true;
        while ((fr ? spfa() : dijkstra())) {
            for (int i = 0; i < n; i++) {
                dis[i] += pot[i] - pot[s];
            }
            Tf f = INF_FLOW;
            for (int i = t; i != s; i = edges[rt[i] ^ 1].to) {
                f = min(f, edges[rt[i]].cap - edges[rt[i]].flow);
            }
            f = min<Tf>(f, budget / dis[t]);
            for (int i = t; i != s; i = edges[rt[i] ^ 1].to) {
                edges[rt[i]].flow += f;
                edges[rt[i] ^ 1].flow -= f;
            }
            flow += f;
            budget -= f * dis[t];
            cost += f * dis[t];
            fr = false;
            swap(dis, pot);
            if (budget == 0 || f == 0) {
                break;
            }
        }
        return {flow, cost};
    }
    void reset() {
        for (int i = 0; i < m; i++) {
            edges[i].flow = 0;
        }
    }
};