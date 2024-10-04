#include <bits/stdc++.h>
using namespace std;
struct CenDecom {
    int n;
    vector<vector<int>> adj;
    vector<bool> vis;
    vector<int> siz;
    CenDecom(int n_ = 0) { init(n_); }
    void init(int n_) {
        n = n_;
        adj.assign(n, {});
        vis.assign(n, false);
        siz.assign(n, 1);
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void get_siz(int x, int p = -1) {
        siz[x] = 1;
        for (int y : adj[x]) {
            if (y == p || vis[y]) {
                continue;
            }
            get_siz(y, x);
            siz[x] += siz[y];
        }
    }
    int get_cen(int x, int sz, int p = -1) {
        for (int y : adj[x]) {
            if (y == p || vis[y]) {
                continue;
            }
            if (siz[y] * 2 > sz) {
                return get_cen(y, sz, x);
            }
        }
        return x;
    }
    void get_ans(int x, int p) {
        // do something
        for (int y : adj[x]) {
            if (y == p || vis[y]) {
                continue;
            }
            get_ans(y, x);
        }
    }
    void work(int x = 0) {
        get_siz(0, x);
        int cen = get_cen(x, siz[x]);
        vis[cen] = true;
        for (int y : adj[cen]) {
            if (vis[y]) {
                continue;
            }
            get_ans(y, cen);
        }
        for (int y : adj[cen]) {
            if (vis[y]) {
                continue;
            }
            work(y);
        }
    }
};