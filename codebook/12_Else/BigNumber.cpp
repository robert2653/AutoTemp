struct BigNum { // require Mint and NTT ~idft
    int sgn;
    string x;
    BigNum() : x("0"), sgn(1) {}
    BigNum(string x, int sgn) : x(norm(x)), sgn(x == "0" ? 1 : sgn) {}
    BigNum(string s) {
        if (s.empty()) {
            *this = BigNum();
        } else if (s[0] == '-') {
            sgn = -1;
            x = s.substr(1);
        } else {
            sgn = 1;
            x = s;
        }
        x = norm(x);
    }
    string norm(string s) const {
        if (s.empty()) return "0";
        reverse(s.begin(), s.end());
        while (s.length() > 1 && s.back() == '0') s.pop_back();
        reverse(s.begin(), s.end());
        return s;
    }
    int cmp(string a, string b) { // abs cmp
        if (a.length() != b.length()) {
            return a.length() - b.length();
        } else {
            return (a < b ? -1 : a > b);
        }
    }
    string Add(const string &a, const string &b) {
        int n = a.length() - 1, m = b.length() - 1, c = 0;
        string res;
        while (n >= 0 || m >= 0 || c) {
            int x = (n >= 0 ? a[n] - '0' : 0) + (m >= 0 ? b[m] - '0' : 0) + c;
            res += (x % 10) + '0', c = x / 10;
            n--, m--;
        }
        reverse(res.begin(), res.end());
        return norm(res);
    }
    string Minus(const string &a, const string &b) {
        int n = a.length() - 1, m = b.length() - 1, bor = 0;
        string res;
        while (n >= 0) {
            int x = a[n] - '0' - bor, y = m >= 0 ? b[m] - '0' : 0;
            bor = 0;
            if (x < y) x += 10, bor = 1;
            res += x - y + '0';
            n--, m--;
        }
        reverse(res.begin(), res.end());
        return norm(res);
    }
    vector<Z> toVector() const {
        vector<Z> res;
        for (int i = x.size() - 1; i >= 0; i--) {
            res.push_back(x[i] - '0');
        }
        return res;
    }
    string fromVector(const vector<Z> &v) {
        string res;
        int carry = 0;
        for (int i = 0; i < v.size(); ++i) {
            carry += v[i].x;
            res += (carry % 10) + '0';
            carry /= 10;
        }
        while (carry) {
            res += (carry % 10) + '0';
            carry /= 10;
        }
        reverse(res.begin(), res.end());
        return norm(res);
    }
    BigNum operator-() const {
        return BigNum(x, -sgn);
    }
    BigNum operator+=(const BigNum &rhs) & {
        if (sgn == 1) {
            if (rhs.sgn == -1) {
                if (cmp(x, rhs.x) < 0) {
                    sgn = -1, x = Minus(rhs.x, x);
                } else {
                    sgn = 1, x = Minus(x, rhs.x);
                }
            } else {
                sgn = 1, x = Add(x, rhs.x);
            }
        } else {
            if (rhs.sgn == -1) {
                sgn = -1, x = Add(x, rhs.x);
            } else {
                if (cmp(x, rhs.x) <= 0) {
                    sgn = 1, x = Minus(rhs.x, x);
                } else {
                    sgn = -1, x = Minus(x, rhs.x);
                }
            }
        }
        return *this;
    }
    BigNum operator-=(const BigNum &rhs) & {
        return *this += -rhs;
    }
    vector<Z> ntt(vector<Z> a, vector<Z> b) {
        if (a.size() < b.size()) {
            swap(a, b);
        }
        int n = 1, tot = a.size() + b.size() - 1;
        while (n < tot) {
            n *= 2;
        }
        if (((P - 1) & (n - 1)) != 0 || b.size() < 128) {
            vector<Z> c(a.size() + b.size() - 1);
            for (int i = 0; i < a.size(); i++) {
                for (int j = 0; j < b.size(); j++) {
                    c[i + j] += a[i] * b[j];
                }
            }
            return c;
        }
        a.resize(n);
        b.resize(n);
        dft(a);
        dft(b);
        for (int i = 0; i < n; ++i) {
            a[i] *= b[i];
        }
        idft(a);
        a.resize(tot);
        return a;
    }
    BigNum operator*=(const BigNum &rhs) & {
        vector<Z> a = toVector(), b = rhs.toVector();
        return BigNum(fromVector(ntt(a, b)), sgn * rhs.sgn);
    }
    friend BigNum operator+(BigNum lhs, BigNum rhs) {
        return lhs += rhs;
    }
    friend BigNum operator-(BigNum lhs, BigNum rhs) {
        return lhs -= rhs;
    }
    friend BigNum operator*(BigNum lhs, BigNum rhs) {
        return lhs *= rhs;
    }
    friend istream &operator>>(istream &is, BigNum &a) {
        string v; is >> v; a = BigNum(v); return is;
    }
    friend ostream &operator<<(ostream &os, const BigNum &a) {
        return os << (a.sgn == 1 ? "" : "-") << a.x;
    }
};