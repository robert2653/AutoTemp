struct KMP {
    string sub;
    vector<int> fail;
    // fail 存匹配失敗時，移去哪
    // 也就是 sub(0, i) 的最長共同前後綴長度
    // ex : a   b  c a b c
    //      -1 -1 -1 0 1 2
    KMP() {}
    KMP(const string &sub_) {
        build(sub_);
    }
    vector<int> build(const string &sub_) {
        sub = sub_;
        fail.resize(sub.size(), -1);
        for (int i = 1; i < sub.size(); i++) {
            int now = fail[i - 1];
            while (now != -1 && sub[now + 1] != sub[i]) {
                now = fail[now];
            }
            if (sub[now + 1] == sub[i]) {
                fail[i] = now + 1;
            }
        }
        return fail;
    }
    vector<int> match(const string &s) {
        vector<int> match;
        for (int i = 0, now = -1; i < s.size(); i++) {
            while (s[i] != sub[now + 1] && now != -1) {
                now = fail[now];
            }
            if (s[i] == sub[now + 1]) {
                now++;
            }
            if (now + 1 == sub.size()) {
                match.push_back(i - now);
                now = fail[now];
            }
        }
        return match;
    }
};