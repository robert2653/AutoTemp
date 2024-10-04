// CF 1932 pF
// 給你很多區間，你可以選一些點，重疊到的線段得到 1 分
// 請問在線段不重複的情況下，最多獲得幾分
int main() {
    int n, m;
    cin >> n >> m;
    // 記錄每點有幾個線段
    // 再一個紀錄，包含這個點的左界
    vector<int> l_side(n + 1, inf), cnt(n + 5, 0);
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        l_side[r] = min(l_side[r], l);
        cnt[l]++;
        cnt[r + 1]--;
    }
    for (int i = 2; i <= n; i++) {
        cnt[i] += cnt[i - 1];
    }
    for (int i = n; i >= 2; i--) {
        l_side[i - 1] = min(l_side[i - 1], l_side[i]);
    }
    vector<int> dp(n + 1);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i] = cnt[i];
        if (l_side[i] != inf) {
            dp[i] += dp[l_side[i] - 1];
        }
        dp[i] = max(dp[i], dp[i - 1]);
    }
    cout << dp[n] << "\n";
}

// CF 1935 pC
// 給你每個事件的 a, b，挑事件會把 a 全部加起來
// 再加上 max(bi) - min(bi)
int main(){
    int n, k, ans = 0;
    cin >> n >> k;
    vector<pair<int, int>> v(n + 1);
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        v[i] = {a, b};
        if (a <= k) ans = 1;
    }
    sort(v.begin() + 1, v.end(), [](pair<int, int> &a, pair<int, int> &b) {
        return a.second < b.second;
    }); // 用 bi 來排，考慮第 i 個時可以先扣
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, inf));
    // 考慮 v[i] 時, 選 j 個的 sum(ai) - min(bi)
    for (int i = 1; i <= n; i++) { // 滾動 dp
        for (int j = n; j >= 2; j--) {
            dp[i][j] = min(dp[i - 1][j], dp[i - 1][j - 1] + v[i].first);
            // min(不選, 選)
            if (dp[i - 1][j - 1] + v[i].first + v[i].second <= k) {
                // 假如可以選，更新 ans 時再加回去 bi
                ans = max(ans, j);
            }
        }
        dp[i][1] = min(dp[i - 1][1], v[i].first - v[i].second);
    }
    cout << ans << "\n";
}