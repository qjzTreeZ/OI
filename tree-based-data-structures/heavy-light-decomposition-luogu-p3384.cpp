#include <bits/stdc++.h>
using namespace std;

//{{{
inline int geti() {
    int x, f = 0;
    char c;
    while (!isdigit(c = getchar()))
        if (c == '-') f = 1;
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
        ;
    return f ? -x : x;
}

inline long long getll() {
    int f = 0;
    long long x;
    char c;
    while (!isdigit(c = getchar()))
        if (c == '-') f = 1;
    for (x = c - '0'; isdigit(c = getchar()); x = x * 10 + c - '0')
        ;
    return f ? -x : x;
}

template <typename T>
void puti(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) puti(x / 10);
    putchar(x % 10 + '0');
}

template <typename T>
void putsp(T x) {
    puti(x);
    putchar(' ');
}

template <typename T>
void putln(T x) {
    puti(x);
    putchar('\n');
}
//}}}

const int N = 100010, E = N << 1;
int n, m, r, p, e0[N], e1[E], dst[E], a[N], bit1[N], bit2[N], depth[N], fa[N], h[N], sz[N], top[N], id[N], cnt = 0;

inline void upd(int *bit, int k, int v) {
    while (k <= n) {
        bit[k] = (bit[k] + v) % p;
        k += k & -k;
    }
}

inline int qry(int *bit, int k) {
    int ret = 0;
    while (k) {
        ret = (ret + bit[k]) % p;
        k &= k - 1;
    }
    return ret;
}

inline void upds(int l, int r, int v) {
    upd(bit1, l, v);
    upd(bit2, l, (long long)v * l % p);
    upd(bit1, r + 1, -v);
    upd(bit2, r + 1, (long long)-v * (r + 1) % p);
}

inline int qrys(int l, int r) {
    return ((long long)(r + 1) * qry(bit1, r) - qry(bit2, r) - (long long)l * qry(bit1, l - 1) + qry(bit2, l - 1)) % p;
}

void dfs1(int u) {
    sz[u] = 1;
    for (int e = e0[u]; e; e = e1[e]) {
        int v = dst[e];
        if (v == fa[u]) continue;
        depth[v] = depth[u] + 1;
        fa[v] = u;
        dfs1(v);
        if (sz[v] > sz[h[u]]) h[u] = v;
        sz[u] += sz[v];
    }
}

void dfs2(int u) {
    id[u] = ++cnt;
    if (!h[u]) return;
    top[h[u]] = top[u];
    dfs2(h[u]);
    for (int e = e0[u]; e; e = e1[e]) {
        int v = dst[e];
        if (v == h[u] || v == fa[u]) continue;
        top[v] = v;
        dfs2(v);
    }
}

int main() {
    n = geti();
    m = geti();
    r = geti();
    p = geti();
    for (int i = 1; i <= n; ++i) a[i] = geti() % p;
    for (int i = 1; i < n; ++i) {
        int x = geti(), y = geti();
        e1[i << 1] = e0[x];
        e0[x] = i << 1;
        dst[i << 1] = y;
        e1[i << 1 | 1] = e0[y];
        e0[y] = i << 1 | 1;
        dst[i << 1 | 1] = x;
    }
    dfs1(r);
    top[r] = r;
    dfs2(r);
    for (int i = 1; i <= n; ++i) upds(id[i], id[i], a[i]);
    while (m--) {
        int o = geti();
        if (o == 1) {
            int x = geti(), y = geti(), z = geti() % p;
            while (top[x] != top[y]) {
                if (depth[top[x]] < depth[top[y]]) swap(x, y);
                upds(id[top[x]], id[x], z);
                x = fa[top[x]];
            }
            if (depth[x] < depth[y]) swap(x, y);
            upds(id[y], id[x], z);
        } else if (o == 2) {
            int x = geti(), y = geti(), ans = 0;
            while (top[x] != top[y]) {
                if (depth[top[x]] < depth[top[y]]) swap(x, y);
                ans = (ans + qrys(id[top[x]], id[x])) % p;
                x = fa[top[x]];
            }
            if (depth[x] < depth[y]) swap(x, y);
            putln(((ans + qrys(id[y], id[x])) % p + p) % p);
        } else if (o == 3) {
            int x = geti(), z = geti() % p;
            upds(id[x], id[x] + sz[x] - 1, z);
        } else {
            int x = geti();
            putln((qrys(id[x], id[x] + sz[x] - 1) % p + p) % p);
        }
    }
    return 0;
}
