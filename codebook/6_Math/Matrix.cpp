template<class T>
vector<vector<T>> operator*(const vector<vector<T>> &a, const vector<vector<T>> &b) {
    int n = a.size(), k = a[0].size(), m = b[0].size();
    assert(k == b.size());
    vector<vector<T>> res(n, vector<T>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int l = 0; l < k; l++) {
                res[i][j] += a[i][l] * b[l][j];
            }
        }
    }
    return res;
}
template<class T>
vector<vector<T>> unit(int n) {
    vector<vector<T>> res(n, vector<T>(n));
    for (int i = 0; i < n; i++) {
        res[i][i] = 1;
    }
    return res;
}
template<class T>
vector<vector<T>> power(vector<vector<T>> a, ll b) {
    int n = a.size();
    assert(n == a[0].size());
    auto res = unit<T>(n);
    for (; b; b /= 2, a = a * a) {
        if (b % 2) {
            res = res * a;
        }
    }
    return res;
}
using Matrix = vector<vector<Z>>;