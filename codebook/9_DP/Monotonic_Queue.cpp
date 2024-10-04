// 應用: dp(i) = h(i) + max(A(j)), for l(i)≤j≤r(i)
// A(j) 可能包含 dp(j), h(i) 可 O(1)
void Bounded_Knapsack() {
    int n, k; // O(nk)
    vector<int> w(n), v(n), num(n);
    deque<int> q;
    // 於是我們將同餘的數分在同一組
    // 每次取出連續 num[i] 格中最大值
    // g_x = max(_{k=0}^num[i] (g'_{x-k} + v_i*k))
    // G_x = g'_{x} - v_i*x
    // x 代 x-k => v_i*(x-k)
    // g_x = max(_{k=0}^num[i] (G_{x-k} + v_i*x))
    vector<vector<ll>> dp(2, vector<ll>(k + 1));
    for (int i = 0; i < n; i++) {
        for (int r = 0; r < w[i]; r++) { // 餘數
            q.clear(); // q 記錄在 x = i 時的 dp 有單調性
            for (int x = 0; x * w[i] + r <= k; x++) {
                while (!q.empty() && q.front() < x - num[i]) {
                    q.pop_front(); // 維護遞減
                }
                ll nxt = dp[0][x * w[i] + r] - x * v[i];
                while (!q.empty() && dp[0][q.back() * w[i] + r] - q.back() * v[i] < nxt) {
                    q.pop_back();
                }
                q.push_back(x);
                dp[1][x * w[i] + r] = dp[0][q.front() * w[i] + r] - q.front() * v[i] + x * v[i];
            }
        }
        swap(dp[0], dp[1]);
    }
    cout << dp[0][k] << "\n";
}