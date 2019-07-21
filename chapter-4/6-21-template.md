第十讲

## 试除法判定质数

```c++
bool is_prime(int x) {
    if (x < 2) return false;
    for (int i = 2; i <= x / i; i ++ )
        if (x % i == 0)
            return false;
    return true;
}
```

## 试除法分解质因数

```c++
void divide(int x) {
    for (int i = 2; i <= x / i; i ++ )
        if (x % i == 0) {
            int s = 0;
            while (x % i == 0) x /= i, s ++ ;
            cout << i << ' ' << s << endl;
        }
    if (x > 1) cout << x << ' ' << 1 << endl;
    cout << endl;
}
```

## 朴素筛法求素数

```c++
int primes[N], cnt;		// primes[]存储所有素数
bool st[N];			// st[x]存储x是否被筛掉

void get_primes(int n) {
    for (int i = 2; i <= n; i ++ ) {
        if (st[i]) continue;
        primes[cnt ++ ] = i;
        for (int j = i; j <= n; j += i)
            st[j] = true;
    }
}
```

## 线性筛法求素数

```c++
int primes[N], cnt;		// primes[]存储所有素数
bool st[N];			// st[x]存储x是否被筛掉

void get_primes(int n) {
    for (int i = 2; i <= n; i ++ ) {
        if (!st[i]) primes[cnt ++ ] = i;
        for (int j = 0; primes[j] <= n / i; j ++ ) {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}
```

## 试除法求所有约数

```c++
vector<int> get_divisors(int x) {
    vector<int> res;
    for (int i = 1; i <= x / i; i ++ )
        if (x % i == 0) {
            res.push_back(i);
            if (i != x / i) res.push_back(x / i);
        }
    sort(res.begin(), res.end());
    return res;
}
```

## 约数个数和约数之和

> 如果 `N = p1^c1 * p2^c2 * ... *pk^ck`
> 约数个数： `(c1 + 1) * (c2 + 1) * ... * (ck + 1)`
> 约数之和：` (p1^0 + p1^1 + ... + p1^c1) * ... * (pk^0 + pk^1 + ... + pk^ck)`

## 欧几里得算法

```c++
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
```

## 求欧拉函数

```c++
int phi(int x) {
    int res = x;
    for (int i = 2; i <= x / i; i ++ )
        if (x % i == 0) {
            res = res / i * (i - 1);
            while (x % i == 0) x /= i;
        }
    if (x > 1) res = res / x * (x - 1);
    
    return res;
}

```

## 筛法求欧拉函数

```c++
int primes[N], cnt;		// primes[]存储所有素数
int euler[N];			// 存储每个数的欧拉函数
bool st[N];			// st[x]存储x是否被筛掉


void get_eulers(int n) {
    euler[1] = 1;
    for (int i = 2; i <= n; i ++ ) {
        if (!st[i]) {
            primes[cnt ++ ] = i;
            euler[i] = i - 1;
        }
        for (int j = 0; primes[j] <= n / i; j ++ ) {
            int t = primes[j] * i;
            st[t] = true;
            if (i % primes[j] == 0) {
                euler[t] = euler[i] * primes[j];
                break;
            }
            euler[t] = euler[i] * (primes[j] - 1);
        }
    }
}
```

## 快速幂

> 求 `m^k mod p`，时间复杂度 `O(logk)`。

```c++
int qmi(int m, int k, int p) {
    int res = 1, t = m;
    while (k) {
        if (k&1) res = res * t % p;
        t = t * t % p;
        k >>= 1;
    }
    return res;
}
```

## 扩展欧几里得算法

```c++
// 求x, y，使得ax + by = gcd(a, b)
int exgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1; y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= (a/b) * x;
    return d;
}
```

