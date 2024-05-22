struct cmp {    // 在有 template 的資結使用
    bool operator()(const int &a, const int &b) const {
        return a < b;
    }
// sort, bound 不用 struct
// priority queue 小到大是 > , set 是 <
// set 不能 = , multiset 要 = 
// 每個元素都要比到，不然會不見
// pbds_multiset 不要用 lower_bound
// 如果要 find, 插入 inf 後使用 upper_bound
// 內建 multiset 可以跟 set 一樣正常使用
// 如果有自定義比較結構就比照以上
};

struct cmp {    // 要在 template 的資結用外部變數
    vector<int> &v;
    cmp(vector<int>& vec) : v(vec) {}
    bool operator() (int a, int b) const {
        return v[a] > v[b];
    } 
// main: cmp cmp1(vector);
// priority_queue<int, vector<int>, cmp> pq(cmp1);
};