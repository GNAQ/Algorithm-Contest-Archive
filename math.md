<h1><center><span style="font-family: Constantia"> Bloom in to you </span></center></h1>

<center><font face="Constantia" color="white">source:NCo Prac26</font></center>

`math.cpp` `math.in` `math.out`

时空限制 `2400ms` `256MiB`

<center><img src="bkg2.jpg" height=50% width=50%/></center>

—— “ 我好像会喜欢上你。”

<center><img src="bkg3.jpg" height=50% width=50%/></center>

—— “ 我也想喜欢七海学姐。”

那句话真正的意义，现在的我还并不知晓……

<center><img src="bkg.jpg" height=50% width=50%/></center>

为什么会这样呢，明明只想了解特别的含义，明明好不容易才明白特别的含义，明明第一次有了喜欢的人，明明只有我才能成为你特别的存在，但是....

七海学姐，你知道吗 :

$$ \varphi(n) = \sum _{d|n} { d \mu ( \frac{n}{d} ) } $$

如果前辈能回答出 :

$$F(n) = \sum_{d|n} { d^k \mu( \frac{n}{d} ) }$$

前辈没有我也没问题了吧。

<center><img src="bkg4.jpg" height=50% width=50%></center>

$\varphi$ 为 `欧拉函数` , $\mu$ 为 `莫比乌斯函数` 。

### 输入格式

第一行两个空格分隔的两个正整数 $m$ 和 $k$ , 其中 $m$ 是询问次数。

之后的 $m$ 行 , 每行一个整数 $n_i$ 。

### 输出格式

输出共 $m$ 行，每行一个整数表示求得的 $F(n_i)$ 。

### 样例数据

#### 样例输入

```plain
1 3
8
```

#### 样例输出

```plain
448
```

### 数据范围

对于 $10\%$ 的数据 , $m=1$ 。

对于 $100\%$ 的数据 , $ m \leqslant 5 \times 10^5 \,,\, n \leqslant 5 \times 10^6 \,,\, 1 \leqslant k \leqslant 100$ 。
