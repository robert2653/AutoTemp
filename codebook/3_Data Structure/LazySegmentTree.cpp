template<class Info, class Tag>
struct LazySeg {    // 左閉右開寫法
    int n;
    vector<Info> info;
    vector<Tag> tag;
    LazySeg() : n(0) {}
    LazySeg(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    LazySeg(vector<Info> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) {
        init(vector(n_, v_));
    }
    void init(vector<Info> init_) {
        n = init_.size();
        info.assign(4 << __lg(n), Info());
        tag.assign(4 << __lg(n), Tag());
        function <void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init_[l];
                return;
            }
            int m = (l + r) / 2;
            build(p * 2, l, m);
            build(p * 2 + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) {
        info[p] = info[p * 2] + info[p * 2 + 1];
    }
    void apply(int p, int l, int r, const Tag &v) {
        info[p].apply(l, r, v);
        tag[p].apply(v);
    }
    void push(int p, int l, int r) {
        int m = (l + r) / 2;
        if (r - l >= 1) {
            apply(p * 2, l, m, tag[p]);
            apply(p * 2 + 1, m, r, tag[p]);
        }
        tag[p] = Tag();
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p, l, r);
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &i) {
        modify(1, 0, n, p, i);
    }
    Info query(int p, int l, int r, int ql, int qr) {
        if (qr <= l || ql >= r) {
            return Info();
        }
        if (ql <= l && r <= qr) {
            return info[p];
        }
        int m = (l + r) / 2;
        push(p, l, r);
	    return query(p * 2, l, m, ql, qr) + query(p * 2 + 1, m, r, ql, qr);
    }
    Info query(int ql, int qr) {
        return query(1, 0, n, ql, qr);
    }
    void range_apply(int p, int l, int r, int ql, int qr, const Tag &v) {
        if (qr <= l || ql >= r) {
            return;
        }
        if (ql <= l && r <= qr) {
            apply(p, l, r, v);
            return;
        }
        int m = (l + r) / 2;
        push(p, l, r);
        range_apply(p * 2, l, m, ql, qr, v);
        range_apply(p * 2 + 1, m, r, ql, qr, v);
        pull(p);
    }
    void range_apply(int l, int r, const Tag &v) {
        range_apply(1, 0, n, l, r, v);
    }
    template<class F>   // 尋找區間內，第一個符合條件的
    int findFirst(int p, int l, int r, int x, int y, F &&pred) {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y && !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        push(p);
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    template<class F>   // 若要找 last，先右子樹遞迴即可
    int findFirst(int l, int r, F &&pred) {
        return findFirst(1, 0, n, l, r, pred);
    }
};
struct Tag { // 有些 Tag 不用 push 例如 sweepLine
    int set_val; int add;
    void apply(const Tag& v) {
        if (v.set_val) {
            set_val = v.set_val;
            add = v.add;
        }
        else {
            add += v.add;
        }
    }
};
struct Info {
    int sum;
    void apply(int l, int r, const Tag &v) {
        if (v.set_val) {
            sum = (r - l) * v.set_val;
        }
        sum += (r - l) * v.add;
    }
    // Info &operator=(const Info &rhs) {
    //     // 部分 assignment 使用
    //     return *this;
    // }
};
Info operator+(const Info &a, const Info &b) {
    return { a.sum + b.sum };
}