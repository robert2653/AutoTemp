struct kthPST : PST<int> {
    int len = 0;
    kthPST(int n_, int len_) { // 數組大小, 離散化後大小
        init(n_);
        len = len_;
        rt.resize(len);
    }
    int modify(int t, int l, int r, int x, int v) {
        t = t ? t : generate();
        if (r - l == 1) {
            nd[t].info += v;
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
    void add(int pos, int x, int val) { // 原數組位置, 離散化位置, 加值
        if (rt.size() < n) {
            rt.resize(n);
        }
        for (int i = pos + 1; i <= n; i += i & -i) {
            rt[i - 1] = modify(rt[i - 1], 0, len, x, val);
        }
    }
    int query(vector<int> &rta, vector<int> &rtb, int l, int r, int k) {
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = 0;
        for (auto x : rta) {
            res -= nd[nd[x].lc].info;
        }
        for (auto x : rtb) {
            res += nd[nd[x].lc].info;
        }
        if (res >= k) {
            for (auto &x : rta) {
                x = nd[x].lc; 
            }
            for (auto &x : rtb) {
                x = nd[x].lc;
            }
            return query(rta, rtb, l, m, k); 
        } else {
            for (auto &x : rta) {
                x = nd[x].rc; 
            }
            for (auto &x : rtb) {
                x = nd[x].rc;
            }
            return query(rta, rtb, m, r, k - res); 
        }
    }
    int query(int l, int r, int k) {
        vector<int> rta, rtb;
        for (int i = l; i > 0; i -= i & -i) {
            rta.push_back(rt[i - 1]);
        }
        for (int i = r; i > 0; i -= i & -i) {
            rtb.push_back(rt[i - 1]);
        }
        return query(rta, rtb, 0, len, k);
    }
};
int dct(int x, vector<int> &a) {
    return lower_bound(a.begin(), a.end(), x) - a.begin();
}