定义拆分数函数 $p(n)$ 为把 $n$ 拆为若干正整数之和的方案数, 如 $p(4)=5$

设 $p'(n)$ 为 $n$ 的满足以下条件的拆分方案数

1. $ a_1 \leqslant a_2 \leqslant \cdots \leqslant a_k $

2. $ a_1 + a_2 + \cdots + a_k = n $

3. $ a_i $ 为奇数

现在给定一个 $n$ , 求

$$
\sum_{i=0}^{n}p'(i)
$$


-------

其实 **奇分拆** 和 **差分拆** 的个数是一样的, 可以通过杨表证明

差分拆是

1. 拆分方案中满足 $a_1 > a_2 > \cdots > a_k$

2. $a_1 + a_2 + \cdots + a_k = n$

然后生成函数一波跑 NTT

$$
\sum_{i=0}^{\infty} p'(i)x^i = \prod_{j=1}^{\infty}(1+x^j)
$$

