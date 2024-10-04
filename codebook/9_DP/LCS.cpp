int main() {
    int m, n;
    cin >> m >> n;
    string s1, s2;
    cin >> s1 >> s2;
    int L = 0;
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    int length = dp[m][n];
    cout << length << "\n";
    string s(length, 'c'); // backtracking
    while (m >= 1 && n >= 1) {
        if (s1[m - 1] == s2[n - 1]) {
            s[length - 1] = s1[m - 1];
            m--, n--, length--;
        }
        else {
            if (dp[m - 1][n] > dp[m][n - 1]) {
                m--;
            } else {
                n--;
            }
        }
    }
    cout << s << "\n";
}