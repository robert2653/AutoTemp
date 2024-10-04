struct DSU {
    int n;
    vector<int> boss, siz;
    DSU() {}
    DSU(int n_) {
        init(n_);
    }
    void init(int n_ = 0) {
        n = n_;
        boss.resize(n);
        iota(boss.begin(), boss.end(), 0);
        siz.assign(n, 1);
    }
    int find(int x) {
        if (boss[x] == x) return x;
        return boss[x] = find(boss[x]);
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        if (siz[x] < siz[y]) {
            swap(x, y);
        }
        siz[x] += siz[y];
        boss[y] = x;
        n--;
        return true;
    }
    int size(int x) {
        return siz[find(x)];
    }
};

struct DSU {
    int n;
    vector<int> boss, siz, stk;
    DSU(int n_ = 0) {
        init(n_);
    }
    void init(int n_) {
        n = n_;
        boss.resize(n);
        iota(boss.begin(), boss.end(), 0);
        siz.assign(n, 1);
        stk.clear();
    }
    int find(int x) {
        return x == boss[x] ? x : find(boss[x]);
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        if (siz[x] < siz[y]) {
            swap(x, y);
        }
        siz[x] += siz[y];
        boss[y] = x;
        n--;
        stk.push_back(y);
        return true;
    }
    void undo(int x) {
        while (stk.size() > x) {
            int y = stk.back();
            stk.pop_back();
            n++;
            siz[boss[y]] -= siz[y];
            boss[y] = y;
        }
    }
    int size(int x) {
        return siz[find(x)];
    }
};