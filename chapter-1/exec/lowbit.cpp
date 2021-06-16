#include<iostream>

using namespace std;

/**
 * 位运算常用模版：
 * 1. n 的二进制中第 K 位是几？
 *      - 先把第 K 位移动到最后一位：n >> k
 *      - 看个位是几：n >> k & 1
 * 2. lowbit：返回 x 最后一位 1 (树状数组的依赖操作)
 *      - x & (-x)
 *      - (-x) 是 x 的补码 -> (-x = ~x + 1) [x取反 + 1]
 *    作用：
 *      1. 可以统计一个数里面有多少个1
 */
int lowbit(int x) {
    return x & (-x);
}

int n;
int main() {
    cin >> n;
    while (n--) {
        int x;
        cin >> x;

        int res = 0;
        while (x != 0) {
            x -= lowbit(x);
            res++;
        }

        cout << res << " ";
    }

    return 0;
}
