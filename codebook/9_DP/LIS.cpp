int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    int dp[n], L = 1;
    dp[0] = 1;
    vector<int> stk {v[0]};
    for (int i = 1; i < n; i++) {
        if (v[i] > stk.back()) {
            stk.push_back(v[i]);
            dp[i] = ++L;
        } else {
            auto it = lower_bound(stk.begin(), stk.end(), v[i]);
            *it = v[i];
            dp[i] = it - stk.begin() + 1;
        }
    }
    vector<int> ans; cout << L << "\n";
    for (int i = n - 1; i >= 0; i--) {
        if (dp[i] == L) {
            ans.push_back(v[i]);
            L--;
        }
    }
    reverse(ans.begin(), ans.end());
    for (auto i : ans) {
        cout << i << " ";
    }
}