// 兩個人比賽，每個人輪流取一個數字且只能是頭尾
// 問兩人都選得好，第一出手的人可取得的最大分數
int main() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<vector<ll>> dp(n, vector<ll>(n));
    // i 到 j 區間的最大 diff
    for (int i = n - 1; i >= 0; i--) {
        dp[i][i] = a[i];
        for (int j = i + 1; j < n; j++) {
            dp[i][j] = max(a[i] - dp[i + 1][j], a[j] - dp[i][j - 1]);
        }
    }
    // x + y = sum; // x - y = dp[0][n - 1]
    cout << (accumulate(a.begin(), a.end(), 0LL) + dp[0][n - 1]) / 2 << "\n";
}