struct PAM {
    // 0 -> even root, 1 -> odd root
    static constexpr int ALPHABET_SIZE = 26;
    struct Node {
        int len;
        int fail;
        array<int, ALPHABET_SIZE> next;
        Node() : len{}, fail{}, next{} {}
    };
    vector<int> s;
    vector<Node> t;
    PAM() {
        init();
    }
    void init() {
        t.assign(2, Node());
        s.clear();
        t[0].len = 0;
        t[1].len = -1;
        t[0].fail = 1;
    }
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    int extend(int p, int c) {
        int n = s.size();
        s.push_back(c);
        while (s[n - t[p].len - 1] != c) {
            p = t[p].fail;
        }
        if (!t[p].next[c]) {
            int r = newNode();
            t[r].len = t[p].len + 2;
            int cur = t[p].fail;
            while (s[n - t[cur].len - 1] != c) {
                cur = t[cur].fail;
            }
            t[r].fail = t[cur].next[c];
            t[p].next[c] = r;
        }
        p = t[p].next[c];
        return p;
    }
};
void solve() {
    string s;
    cin >> s;
    int n = s.length();
    vector<int> last(n + 1);
    last[0] = 1;
    PAM pam;
    for (int i = 0; i < n; i++) {
        last[i + 1] = pam.extend(last[i], s[i] - 'a');
    }
    int sz = pam.t.size();
    vector<int> cnt(sz);
    for (int i = 1; i <= n; i++) {
        cnt[last[i]]++; // 去重 = 1
    }
    for (int i = sz - 1; i > 1; i--) {
        cnt[pam.t[i].fail] += cnt[i];
    }
}