# 面包的某(神仙)题

------

## 题目描述

给定 $T$ 组 $n$ ，求出

$$
\sum_{i=1}^{n}\sum_{j=1}^{n}[\gcd(i,j)=i \oplus j]
$$

## 数据范围

$ T \leqslant 10^5 \,,\, n \leqslant 3 \times 10^7$

------

## 题解

+ $ a-b \leqslant a \oplus b  \,\,(a \geqslant b)$

+ $ a \oplus b =c \Leftrightarrow a \oplus c = b $

+ $ \gcd(a,b)=c$

$ \text{suppose } a=k_1c \,,\, b=k_2c \,\,(a \geqslant b \,,\, \gcd(k_1,k_2)=1 )$

$ \therefore a-b=(k_1-k_2)c $

$ \therefore a-b \geqslant c $

$ \because a-b \leqslant a \oplus b $

$ \therefore a-b \leqslant c $

$ \therefore a-b=c $

枚举 $c$ , 枚举一个 $a \,\, (b=a-c)$ ， 直接判断 $ a \oplus b =c$ 即可。

注： $\gcd(a,b)=\gcd(a,a-c)=c$ ，所以 $\gcd(a,c)=c \,,\, c|a$ ，枚举倍数即可。

**复杂度**：据调和级数可积得复杂度为 $O(n \ln n)$

证明:

$$
H(n) = \sum_{x=1}^n \frac{1}{x} = \sum_{i=1}^n \int_i^{i+1} \frac{1}{\lfloor x \rfloor}dx
$$

$$ 
=\int_1^{n+1} \frac{1}{x} + \frac{1}{\lfloor x \rfloor} - \frac{1}{x} dx
$$

$$
=\int_1^{n+1} \frac{1}{x}dx + \int_1^{n+1} \frac{1}{ \lfloor x \rfloor } - \frac{1}{x}dx
$$

$$
\approx \ln(n+1) + \gamma
$$

$$
(\gamma \xlongequal{\mathrm{def}} \lim_{n \rightarrow \infty} \int_1^n \frac{1}{ \lfloor x \rfloor } - \frac{1}{x}dx \approx 0.57721566490153286060651209)
$$