# Cf 507C

------

给定一张图，点 $i$ 的权为 $c_i \in [0,2^k-1]$ 。有 $m$ 条无向边。

定义一个图是`安全`的，当且仅当对于所有的 $(u,v) \in E \,,\, c_u \ne c_ v$ 。

定义图的一个变换 $(A,x)$ ( 一个点集 $A \subseteq V $ ，一个权值 $x \in [0,2^k-1]$ ) 是点集 $A$ 中的所有点 $u$ 权值都变为 $c_u \oplus x$ 。

求出`安全`的变换的数量 ( $\mod 10^9+7$ )

(变换之间相互独立)

-----

$1 \leqslant n \leqslant 5 \times 10^5 \,,\, 0 \leqslant m \leqslant \min( \frac{n(n-1)}{2} ,5 \times 10^5) \,,\, 0 \leqslant k \leqslant 60$

