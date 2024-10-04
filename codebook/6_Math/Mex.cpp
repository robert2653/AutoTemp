template<class T>
int mex(vector<T> &v) {
    unordered_set<T> s;
    for (auto e : v) {
        s.insert(e);
    }
    for (T i = 0; ; i++) {
        if (s.find(i) == s.end()) {
            return i;
        }
    }
}