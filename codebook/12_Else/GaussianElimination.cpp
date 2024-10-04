// 找反矩陣就開 2n，右邊放單位矩陣, 做完檢查左半是不是單位, 回傳右半
// 0  : no solution
// -1 : infinity solution
// 1  : one solution
template<class T>
tuple<T, int, vector<T>> gaussianElimination(vector<vector<T>> a) {
    int n = a.size(), m = a[0].size(), rk = 0, sgn = 1;
    T det = 1;
    bool zero_det = false;
    for (int c = 0; c < n; c++) {
        int p = -1;
        for (int r = rk; r < n; r++) {
            if (a[r][c] != 0) {
                p = r;
                break;
            }
        }
        if (p == -1) {
            zero_det = true;
            continue;
        }
        if (p != rk) swap(a[rk], a[p]), sgn *= -1;
        det *= a[rk][c];
        T inv = 1 / a[rk][c];
        for (int j = c; j < m; j++) a[rk][j] *= inv;
        for (int r = 0; r < n; r++) {
            if (r == rk || a[r][c] == 0) {
                continue;
            }
            T fac = a[r][c];
            for (int j = c; j < m; j++) {
                a[r][j] -= fac * a[rk][j];
            }
        }
        rk++;
    }
    det = (zero_det ? 0 : det * sgn);
    for (int r = rk; r < n; r++) {
        if (a[r][m - 1] != 0) {
            return {det, 0, {}};
        }
    }
    if (rk < n) {
        return {det, -1, {}};
    }
    vector<T> ans(n);
    for (int i = 0; i < n; i++) {
        ans[i] = a[i][m - 1];
    }
    return {det, 1, ans};
}
template<class T>
tuple<int, vector<T>, vector<vector<T>>> findBasis(vector<vector<T>> a) {
    int n = a.size(), m = a[0].size(), rk = 0;
    vector<int> pos(m - 1, -1);
    for (int c = 0; c < m - 1; c++) {
        int p = -1;
        for (int r = rk; r < n; r++) {
            if (a[r][c] != 0) {
                p = r;
                break;
            }
        }
        if (p == -1) {
            continue;
        }
        if (p != rk) {
            swap(a[rk], a[p]);
        }
        pos[c] = rk;
        T inv = 1 / a[rk][c];
        for (int j = c; j < m; j++) {
            a[rk][j] *= inv;
        }
        for (int r = 0; r < n; r++) {
            if (r == rk || a[r][c] == 0) {
                continue;
            }
            T fac = a[r][c];
            for (int j = c; j < m; j++) {
                a[r][j] -= fac * a[rk][j];
            }
        }
        rk++;
    }
    vector<T> sol(m - 1);
    vector<vector<T>> basis;
    for (int r = rk; r < n; r++) {
        if (a[r][m - 1] != 0) {
            return {-1, sol, basis};
        }
    }
    for (int c = 0; c < m - 1; c++) {
        if (pos[c] != -1) {
            sol[c] = a[pos[c]][m - 1];
        }
    }
    for (int c = 0; c < m - 1; c++) {
        if (pos[c] == -1) {
            vector<T> v(m - 1);
            v[c] = 1;
            for (int j = 0; j < m - 1; j++) {
                if (pos[j] != -1) {
                    v[j] = -a[pos[j]][c];
                }
            }
            basis.push_back(v);
        }
    }
    return {rk, sol, basis};
}
template<class T>
using Matrix = vector<vector<T>>;