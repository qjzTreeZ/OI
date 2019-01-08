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

const int K = 110, B = 30;
int k, a[K], lb[B + 1];
long long ans = 0;

inline bool ins(int x) {
    for (int i = B; i >= 0; --i)
        if (x & 1 << i) {
            if (!lb[i]) {
                lb[i] = x;
                return true;
            } else
                x ^= lb[i];
        }
    return false;
}

int main() {
    k = geti();
    for (int i = 1; i <= k; ++i) a[i] = geti();
    sort(a + 1, a + 1 + k, greater<int>());
    for (int i = 1; i <= k; ++i)
        if (!ins(a[i])) ans += a[i];
    putln(ans);
    return 0;
}