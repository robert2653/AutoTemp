void dfs(int x) {
    col[x] = 1;
    for (auto y : graph[x]) {
        par[y] = x;
        if (col[y] == 1) {
            // found cycle
        }
        else if (col[y] == 0) {
            dfs(y);
        }
    }
    col[x] = 2;
}