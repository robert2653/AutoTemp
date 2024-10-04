struct Comb {
    ll n;
    vector<Z> _fac, _invfac, _inv;
    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    Comb(ll n) : Comb() { init(n); }
    void init(ll m) {
        m = min(m, Z::getMod() - 1);
        if (m <= n) return;
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);
        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _invfac[m] = _fac[m].inv();
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i] = _invfac[i] * _fac[i - 1];
        }
        n = m;
    }
    Z fac(ll m) {
        if (m > n) {
            init(2 * m);
        }
        return _fac[m];
    }
    Z invfac(ll m) {
        if (m > n) {
            init(2 * m);
        }
        return _invfac[m];
    }
    Z inv(ll m) {
        if (m > n) {
            init(2 * m);
        }
        return _inv[m];
    }
    Z binom(ll n, ll m) {
        if (n < m || m < 0) {
            return 0;
        }
        return fac(n) * invfac(m) * invfac(n - m);
    }
    Z lucas(ll n, ll m) { // Mod 要在 1E5 左右
        if (m == 0) {
            return 1;
        }
        return binom(n % Z::getMod(), m % Z::getMod()) * lucas(n / Z::getMod(), m / Z::getMod());
    }
} comb; // 注意宣告, 若要換模數需重新宣告