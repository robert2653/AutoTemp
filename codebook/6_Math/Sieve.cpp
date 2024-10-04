vector<int> primes, minp;
void sieve(int n) {
    minp.assign(n + 1, 0);
    primes.clear();
    // minp[i] == i, 質數
    for (int i = 2; i <= n; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            primes.push_back(i);
        }
        for (auto p : primes) {
            if (i * p > n) {
                break;
            }
            minp[i * p] = p;
            if (p == minp[i]) {
                break;
            }
        }
    }
}
// a ^ (m-1) = 1 (Mod m)
// a ^ (m-2) = 1/a (Mod m)
// Exp2: cout << power(x, power(y, p, Mod - 1), Mod)
// Num = (x+1) * (y+1) * (z+1)...
// Sum = (a^0 + a^1+...+ a^x) * (b^0 +...+ b^y)
// Mul = N * (x+1) * (y+1) * (z+1) / 2