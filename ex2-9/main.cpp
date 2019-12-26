/*
 * @Date         : 2019-12-20 08:11:39
 * @Author       : ssyze
 * @Description  : ex2-9
 */
/*
 *  题意明确：求任意两点间最大权值最小的路径
 *  可以想到，求任意两点间最短路径利用floyd算法
 *  转移方程为g[i][j]=min(g[i][j],g[i][k]+g[k][j])
 *  利用寻找是否存在中转顶点实现对最短路径的松弛
 *  该题思路类似，由于求的是最大权值最小的路径
 *  转移方程改为g[i][j]=min(max(g[i][k],g[k][j]),g[i][j])
 *  寻找是否存在中转顶点，使中转路径的最大权值小于当前路径的最大权值
 *  若存在这样的顶点，则更新路径最大值，最后可以得到任意两点间最大权值最小的路径
 */
#include <bits/stdc++.h>
using namespace std;
const int inf = 0x3f3f3f3f;
const int maxn = 105;
int g[maxn][maxn];
int n, m, q;
int main()
{
    cin >> n >> m >> q;
    memset(g, inf, sizeof(g));
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a][b] = c;
        g[b][a] = c;
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                g[i][j] = min(max(g[i][k], g[k][j]), g[i][j]);
            }
        }
    }
    while (q--) {
        int x, y;
        cin >> x >> y;
        if (g[x][y] == inf) {
            cout << "no path" << endl;
        }
        else {
            cout << g[x][y] << endl;
        }
    }
}