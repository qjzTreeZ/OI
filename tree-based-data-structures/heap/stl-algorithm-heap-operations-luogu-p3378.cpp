#include <bits/stdc++.h>
using namespace std;

inline int geti() {
    int x, f = 0;
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

const int N = 1000000;
int heap[N], sz = 0;

int main() {
    int n = geti();
    greater<int> cmp;
    while (n--)
        switch (geti()) {
            case 1:
                heap[sz++] = geti();
                push_heap(heap, heap + sz, cmp);
                break;
            case 2:
                putln(heap[0]);
                break;
            case 3:
                pop_heap(heap, heap + sz--, cmp);
                break;
        }
    return 0;
}
