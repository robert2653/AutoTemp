template<class T>
constexpr T power(T a, ll b) {
    T res {1};
    for (; b; b /= 2, a *= a) {
        if (b & 1) {
            res *= a;
        }
    }
    return res;
}
constexpr ll mul(ll a, ll b, ll p) {
    ll res = a * b - ll(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}
template<ll P>
struct MInt {
    ll x;
    constexpr MInt() : x {0} {}
    constexpr MInt(ll x) : x {norm(x % getMod())} {}
    static ll Mod;
    constexpr static ll getMod() {
        return P > 0 ? P : Mod;
    }
    constexpr static void setMod(ll Mod_) {
        Mod = Mod_;
    }
    constexpr ll norm(ll x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr MInt operator-() const {
        return MInt(norm(getMod() - x));
    }
    constexpr MInt inv() const {
        return power(*this, getMod() - 2);
    }
    constexpr MInt &operator*=(MInt rhs) & {
        if (getMod() < (1ULL << 31)) {
            x = x * rhs.x % int(getMod());
        } else {
            x = mul(x, rhs.x, getMod());
        }
        return *this;
    }
    constexpr MInt &operator+=(MInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MInt &operator-=(MInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MInt &operator/=(MInt rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MInt operator*(MInt lhs, MInt rhs) {
        return lhs *= rhs;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs) {
        return lhs += rhs;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs) {
        return lhs -= rhs;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs) {
        return lhs /= rhs;
    }
    friend istream &operator>>(istream &is, MInt &a) {
        ll v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend ostream &operator<<(ostream &os, const MInt &a) {
        return os << a.x;
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs) {
        return lhs.x == rhs.x;
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs) {
        return lhs.x != rhs.x;
    }
    friend constexpr bool operator<(MInt lhs, MInt rhs) {
        return lhs.x < rhs.x;
    }
};
template<>
ll MInt<0>::Mod = 998244353;
constexpr ll P = 1E9 + 7;
using Z = MInt<P>;