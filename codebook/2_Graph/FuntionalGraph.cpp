constexpr int N = 2E5 + 5;
int cht[N][31]; // 倍增表, 放外面不然 TLE
struct FuntionalGraph {
    int n, cnt;
    vector<int> g, bel, id, len, in, top;
    FuntionalGraph() : n(0) {}
    FuntionalGraph(vector<int> g_) { init(g_); }
    void init(vector<int> g_) {
        n = g_.size();
        g = g_;
        cnt = 0;
        bel.assign(n, -1);
        id.resize(n);
        len.clear();
        in.assign(n, 0);
        top.assign(n, -1);
        build();
    }
    void build() {
        for (int i = 0; i < n; i++) {
            cht[i][0] = g[i];
            in[g[i]]++;
        }
        for (int i = 1; i <= 30; i++) {
            for (int u = 0; u < n; u++) {
                cht[u][i] = cht[cht[u][i - 1]][i - 1];
            }
        }
        for (int i = 0; i < n; i++) {
            if (in[i] == 0) {
                label(i);
            }
        }
        for (int i = 0; i < n; i++) {
            if (top[i] == -1) {
                label(i);
            }
        }
    }
    void label(int u) {
        vector<int> p;
        int cur = u;
        while (top[cur] == -1) {
            top[cur] = u;
            p.push_back(cur);
            cur = g[cur];
        }
        auto s = find(p.begin(), p.end(), cur);
        vector<int> cyc(s, p.end());
        p.erase(s, p.end()); p.push_back(cur);
        for (int i = 0; i < (int)cyc.size(); i++) {
            bel[cyc[i]] = cnt;
            id[cyc[i]] = i;
        }
        if (!cyc.empty()) {
            cnt++;
            len.push_back(cyc.size());
        }
        for (int i = p.size() - 1; i > 0; i--) {
            id[p[i - 1]] = id[p[i]] - 1;
        }
    }
    int jump(int u, int k) {
        for (int b = 0; k > 0; b++) {
            if (k & 1) {
                u = cht[u][b];
            }
            k >>= 1;
        }
        return u;
    }
};