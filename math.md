# 欧拉函数

提交名称 `math.cpp` `math.in` `math.out`

时空限制 `2400ms` `256MiB`

`GNAQ` 是欧拉的粉丝。

众所周知 :

$$ \varphi(n) = \sum _{d|n} { d \mu ( \frac{n}{d} ) } $$

$\varphi$ 为 `欧拉函数` , $\mu$ 为 `莫比乌斯函数` 。

请求出 :

$$F(n) = \sum_{d|n} { d^k \mu( \frac{n}{d} ) }$$

### 输入格式

第一行两个空格分隔的两个正整数 $m$ 和 $k$ , 其中 $m$ 是询问次数。

之后的 $m$ 行 , 每行一个整数 $n_i$ 。

### 输出格式

输出共 $m$ 行，每行一个整数表示求得的 $F(n_i)$ 。

### 数据范围

对于 $10\%$ 的数据 , $m=1$ 。

对于 $100\%$ 的数据 , $ m \leqslant 5 \times 10^5 \,,\, n \leqslant 5 \times 10^6 \,,\, 1 \leqslant k \leqslant 100$ 。