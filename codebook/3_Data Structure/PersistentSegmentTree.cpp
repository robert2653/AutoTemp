template<class Info>
struct PST {
    struct Node {
        Info info = Info();
        int lc = 0, rc = 0;
    };
    vector<Node> nd;
    int n = 0;
    vector<int> rt;
    PST() : n(0) {}
    PST(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    PST(vector<Info> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) {
        init(vector<Info>(n_, v_));
    }
    void init(vector<Info> init_) {
        n = init_.size();
        nd.clear();
        rt.clear();
        nd.emplace_back(); // 讓 root 指向 1-based
        rt.push_back(build(0, n, init_));
    }
    int build(int l, int r, vector<Info> &init_) {
        int id = nd.size();
        nd.emplace_back();
        if (r - l == 1) {
            nd[id].info = init_[l];
            return id;
        }
        int m = (l + r) >> 1;
        nd[id].lc = build(l, m, init_);
        nd[id].rc = build(m, r, init_);
        pull(nd[id]);
        return id;
    }
    void pull(Node &t) {
        t.info = nd[t.lc].info + nd[t.rc].info;
    }
    int copy(int t) { // copy 一個 node
        nd.push_back(nd[t]);
        return nd.size() - 1;
    }
    int generate() { // 創立新的 node
        nd.emplace_back();
        return nd.size() - 1;
    }
    int modify(int t, int l, int r, int x, const Info &v) {
        t = t ? copy(t) : generate();
        if (r - l == 1) {
            nd[t].info = v;
            return t;
        }
        int m = (l + r) >> 1;
        if (x < m) {
            nd[t].lc = modify(nd[t].lc, l, m, x, v);
        } else {
            nd[t].rc = modify(nd[t].rc, m, r, x, v);
        }
        pull(nd[t]);
        return t;
    }
    void modify(int ver, int pos, const Info &val) {
        if (int(rt.size()) <= ver) {
            rt.resize(ver + 1);
        }
        rt[ver] = modify(rt[ver], 0, n, pos, val);
    }
    Info query(int t, int l, int r, int ql, int qr) {
        if (l >= qr || r <= ql) {
            return Info();
        }
        if (ql <= l && r <= qr) {
            return nd[t].info;
        }
        int m = (l + r) >> 1;
        return query(nd[t].lc, l, m, ql, qr) + query(nd[t].rc, m, r, ql, qr);
    }
    Info query(int ver, int ql, int qr) {
        return query(rt[ver], 0, n, ql, qr);
    }
    void createVersion(int ori_ver) {
        rt.push_back(copy(rt[ori_ver]));
    }
    void reserve(int n, int q) {
        nd.reserve(n + q * (2 * __lg(n) + 1));
        rt.reserve(q + 1);
    }
    void resize(int n) {
        rt.resize(n);
    }
};
struct Info {
    int sum = 0;
};
Info operator+(const Info &a, const Info &b) {
    return { a.sum + b.sum };
}