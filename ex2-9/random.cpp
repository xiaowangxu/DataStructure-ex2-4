/*
 * @Date         : 2019-12-26 10:40:29
 * @Author       : ssyze
 * @Description  : 
 */
#include <bits/stdc++.h>
using namespace std;
int main()
{
    mt19937 rnd(time(0));
    freopen("data1.txt", "a", stdout);
    int g[11][11] = { 0 };
    int node = 0;
    while (node <= 3) {
        node = (rnd() % 6) + 1;
    }
    int edge = 0, ans = 0;
    while (ans <= node * (node - 3) / 2) {
        ans = rnd() % (node * (node - 1) / 2);
    }
    while (edge < ans) {
        //cout << 1 << endl;
        int x = (rnd() % node) + 1;
        int y = (rnd() % node) + 1;
        if (x == y)
            continue;
        if (g[x][y])
            continue;
        int w = ((rnd() % 100) / 10) * 10;
        if (w == 0)
            continue;
        g[x][y] = w;
        g[y][x] = w;
        edge++;
    }
    //cout << edge << ' ' << ans << endl;
    int k = 0;
    while (k == 0) {
        k = rnd() % node + 2;
    }
    cout << node << ' ' << ans << ' ' << k << '\n';
    for (int i = 1; i <= node; i++) {
        for (int j = 1; j <= node; j++) {
            if (g[i][j]) {
                cout << i << ' ' << j << ' ' << g[i][j] << '\n';
                g[i][j] = g[j][i] = 0;
            }
        }
    }
    for (int i = 0; i < k;) {
        int x = (rnd() % node) + 1;
        int y = (rnd() % node) + 1;
        if (x == y)
            continue;
        cout << x << ' ' << y << '\n';
        i++;
    }
    cout << '\n';
}