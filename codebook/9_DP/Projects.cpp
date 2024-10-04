int main() { // 排程有權重問題，輸出價值最多且時間最少
    struct E {
        int from, to, w, id;
    };
    int n;
    cin >> n;
    vector<E> a(n + 1);
    for (int i = 1; i <= n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        a[i] = {u, v, w, i};
    }
    vector<array<ll, 2>> dp(n + 1); // w, time
    vector<array<int, 2>> rec(n + 1); // 有沒選，上個是誰
    sort(a.begin(), a.end());
    for (int i = 1; i <= n; i++) {
        int id = --lower_bound(all(a), {0, a[i].from}, [](E x, E y) {
            return x.to < y.to;
        }) - a.begin();
        dp[i] = dp[i - 1];
        ll nw = dp[id][0] + a[i].w;
        ll nt = dp[id][1] + a[i].to - a[i].from;
        if (dp[i][0] < nw || dp[i][0] == nw && dp[i][1] > nt) {
            dp[i] = {nw, nt};
            rec[i] = {1, id};
        }
    }
    vector<int> ans;
    for (int i = n; i != 0;) {
        if (rec[i][0]) {
            ans.push_back(a[i].id);
            i = rec[i][1];
        } else {
            i--;
        }
    }
}