constexpr int N = 1E7;
int tot = 0;
int trie[N][26], cnt[N];
void reset() {
    tot = 0;
    fill_n(trie[0], 26, 0);
}
int newNode() {
    int x = ++tot;
    cnt[x] = 0;
    fill_n(trie[x], 26, 0);
    return x;
}
void add(const string &s) {
    int p = 0;
    for (auto c : s) {
        int &q = trie[p][c - 'a'];
        if (!q) {
            q = newNode();
        }
        p = q;
    }
    cnt[p] += 1;
}
int find(const string &s) {
    int p = 0;
    for (auto c : s) {
        int q = trie[p][c - 'a'];
        if (!q) {
            return 0;
        }
        p = q;
    }
    return cnt[p];
}