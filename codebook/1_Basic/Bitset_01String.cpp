#include <bits/stdc++.h>
using namespace std;
#pragma GCC target("popcnt")
int main() {
    // Bitset
    int x; cin >> x;
    bitset<20> b = x; // 讀整數
    cin >> b; // 讀 01 字串
    cout << b.count() << "\n"; // 1 的個數
    cout << b.to_ullong() << "\n"; // 轉整數, overflow 會報錯
    cout << b.to_string() << "\n"; // 轉 01 字串, 跟直接 cout 一樣
    // 讀 01 字串並轉成 int
    string s; cin >> s;
    cout << stoll(s, 0, 2) << "\n";
    return 0;
}