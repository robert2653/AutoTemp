struct Treap {
    Treap *lc, *rc;
    int pri, siz;
    bool rev_valid;

    int val;
    int min;

    Treap(int val_) {
        min = val = val_;
        pri = rand();
        lc = rc = nullptr;
        siz = 1;
        rev_valid = 0;
    }
    void pull() { // update siz or other information
        siz = 1;
        min = val;
        for (auto c : {lc, rc}) {
            if (!c) {
                continue;
            }
            siz += c->siz;
            min = std::min(min, c->min);
        }
    }
    void push() {
        if (rev_valid) {
            swap(lc, rc);
            if (lc) {
                lc->rev_valid ^= 1;
            }
            if (rc) {
                rc->rev_valid ^= 1;
            }
        }
        rev_valid = false;
    }
    int find(int k) { // 找到 min 是 k 的位置 (1-based)
        push();
        int ls = (lc ? lc->siz : 0) + 1;
        if (val == k) {
            return ls;
        }
        if (lc && lc->min == k) {
            return lc->find(k);
        } else {
            return rc->find(k) + ls;
        }
    }
};
int size(Treap *t) {
    return t ? t->siz : 0;
}
Treap *merge(Treap *a, Treap *b) {
    if (!a || !b) {
        return a ? a : b;
    }
    a->push();
    b->push();
    if (a->pri > b->pri) {
        a->rc = merge(a->rc, b);
        a->pull();
        return a;
    }
    else {
        b->lc = merge(a, b->lc);
        b->pull();
        return b;
    }
}
pair<Treap*, Treap*> split(Treap *t, int k) {
    // 分割前 k 個在 first，剩下的在 second
	if (t == nullptr) {
        return {nullptr, nullptr};
    }
    t->push();
	if (size(t->lc) < k) {
		auto [a, b] = split(t->rc, k - size(t->lc) - 1);
		t->rc = a;
		t->pull();
		return {t, b};
	} else {
		auto [a, b] = split(t->lc, k);
		t->lc = b;
		t->pull();
		return {a, t};
	}
}
void Print(Treap *t) {
    if (!t) {
        return;
    }
    t->push();
    Print(t->lc);
    cout << t->val;
    Print(t->rc);
}