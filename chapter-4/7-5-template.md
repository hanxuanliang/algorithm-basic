# 第十二讲

## 高斯消元

```c++
// a[N][N]是增广矩阵
int gauss() {
    int c, r;
    for (c = 0, r = 0; c < n; c ++ ) {
        int t = r;
        for (int i = r; i < n; i ++ )	// 找到绝对值最大的行
            if (fabs(a[i][c]) > fabs(a[t][c]))
                t = i;

        if (fabs(a[t][c]) < eps) continue;

        for (int i = c; i <= n; i ++ ) swap(a[t][i], a[r][i]);		// 将绝对值最大的行换到最顶端
        for (int i = n; i >= c; i -- ) a[r][i] /= a[r][c];		// 将当前上的首位变成1
        for (int i = r + 1; i < n; i ++ )		// 用当前行将下面所有的列消成0
            if (fabs(a[i][c]) > eps)
                for (int j = n; j >= c; j -- )
                    a[i][j] -= a[r][j] * a[i][c];

        r ++ ;
    }

    if (r < n) {
        for (int i = r; i < n; i ++ )
            if (fabs(a[i][n]) > eps)
                return 2; // 无解
        return 1; // 有无穷多组解
    }

    for (int i = n - 1; i >= 0; i -- )
        for (int j = i + 1; j < n; j ++ )
            a[i][n] -= a[i][j] * a[j][n];

    return 0; // 有唯一解
}
```

## 递归法求组合数

```c++
// c[a][b] 表示从a个苹果中选b个的方案数
for (int i = 0; i < N; i ++ )
for (int j = 0; j <= i; j ++ )
    if (!j) c[i][j] = 1;
	else c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
```

## 通过预处理逆元的方式求组合数

首先预处理出所有阶乘取模的余数fact[N]，以及所有阶乘取模的逆元infact[N]
如果取模的数是质数，可以用费马小定理求逆元

```c++
// 快速幂模板
int qmi(int a, int k, int p) {
    int res = 1;
    while (k) {
        if (k & 1) res = (LL)res * a % p;
        a = (LL)a * a % p;
        k >>= 1;
    }
    return res;
}
// 预处理阶乘的余数和阶乘逆元的余数
fact[0] = infact[0] = 1;
for (int i = 1; i < N; i ++ ) {
    fact[i] = (LL)fact[i - 1] * i % mod;
    infact[i] = (LL)infact[i - 1] * qmi(i, mod - 2, mod) % mod;
}
```

## Lucas定理

> 若p是质数，则对于任意整数 `1 <= m <= n`，有：
> 		`C(n, m) = C(n % p, m % p) * C(n / p, m / p) (mod p)`

```c++
// 快速幂模板
int qmi(int a, int k) {
    int res = 1;
    while (k) {
        if (k & 1) res = (LL)res * a % p;
        a = (LL)a * a % p;
        k >>= 1;
    }
    return res;
}

// 通过定理求组合数C(a, b)
int C(int a, int b)	{
    int res = 1;
    for (int i = 1, j = a; i <= b; i ++, j -- ) {
        res = (LL)res * j % p;
        res = (LL)res * qmi(i, p - 2) % p;
    }
    return res;
}

int lucas(LL a, LL b) {
    if (a < p && b < p) return C(a, b);
    return (LL)C(a % p, b % p) * lucas(a / p, b / p) % p;
}
```

## 分解质因数法求组合数

> 当我们需要求出组合数的真实值，而非对某个数的余数时，分解质因数的方式比较好用：
> 		1. 筛法求出范围内的所有质数
> 		2. 通过` C(a, b) = a! / b! / (a - b)! `这个公式求出每个质因子的次数。 n! 中p的次数是 `n / p + n / p^2 + n / p^3 + ...`
> 		3. 用高精度乘法将所有质因子相乘

```c++
int primes[N], cnt;		// 存储所有质数
int sum[N];		// 存储每个质数的次数
bool st[N];		// 存储每个数是否已被筛掉

// 线性筛法求素数
void get_primes(int n){
    for (int i = 2; i <= n; i ++ )
    {
        if (!st[i]) primes[cnt ++ ] = i;
        for (int j = 0; primes[j] <= n / i; j ++ )
        {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

// 求n！中的次数
int get(int n, int p) {
    int res = 0;
    while (n)
    {
        res += n / p;
        n /= p;
    }
    return res;
}

// 高精度乘低精度模板
vector<int> mul(vector<int> a, int b) {
    vector<int> c;
    int t = 0;
    for (int i = 0; i < a.size(); i ++ )
    {
        t += a[i] * b;
        c.push_back(t % 10);
        t /= 10;
    }

    while (t)
    {
        c.push_back(t % 10);
        t /= 10;
    }

    return c;
}

get_primes(a);	// 预处理范围内的所有质数

// 求每个质因数的次数
for (int i = 0; i < cnt; i ++ ) {
    int p = primes[i];
    sum[i] = get(a, p) - get(b, p) - get(a - b, p);
}

vector<int> res;
res.push_back(1);

// 用高精度乘法将所有质因子相乘
for (int i = 0; i < cnt; i ++ )		
    for (int j = 0; j < sum[i]; j ++ )
        res = mul(res, primes[i]);
```

## 卡特兰数

> 给定n个0和n个1，它们按照某种顺序排成长度为2n的序列，满足任意前缀中0的个数都不少于1的个数的序列的数量为： `Cat(n) = C(2n, n) / (n + 1)`