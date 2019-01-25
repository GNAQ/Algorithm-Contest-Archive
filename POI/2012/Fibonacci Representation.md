## Fibonacci Representation

### Problem Description

The Fibonacci number sequence is a sequence of integers defined recursively in the following way :


$$
F_0=0 \,\, F_1=1 \,\, F_n=F_{n-1}+F_{n-2}
$$
The initial elements of this string are : $0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55,\cdots$

Byteasar investigates how different numbers can be represented as sums or differences of Fibonacci numbers. Currently, he is wondering how to find the smallest term of Fibonacci numbers (not necessarily different)  as the sum or difference of these numbers is a given positive integer $k$ . For example, numbers $10, 19, 17$ and $1070$ can be represented minimally, respectively, by means of $2,2, 3$ and $4$ Fibonacci numbers :
$$
10 = 5 + 5
\\
19 = 21 - 2 
\\
17 = 13 + 5 - 1
\\
1070 = 987 + 89 - 5 - 1
$$
Help Byteasar! Write a program which for a given positive integer $k$ determines the minimum number of Fibonacci numbers needed to represent the number $k$ as their sum or difference.

The number of queries $p \leqslant 10$ , and for every $p$ the given intager $k \leqslant 4 \times 10^{17}$.

----------

### Solution

#### Introduction

A positive integer $k$ is given . The number $k$ is represented by a pair of multiset $( P_+ , P_- )$ satisfying the condition:
$$
\sum_{i \in P_+}{F_i} - \sum_{j \in P_-}{F_j} = k
$$
The size of the representation will be the sum of the sizes of multiset  $P_+$ and $P_-$ . We will call one representation optimal if there is no other representation of the number $k$ with a smaller size.

#### First step

​	**Intuitive observation**. First of all, we can accept without losing generality that all elements in $P_+$ and $P_-$ multiset (or indexes of Fibonacci numbers in the representation) are not less than $2$ . Next:

​	**Observation 1.** If there is an index $i$ in the representation of Fibonacci numbers, such that $i \in P_+$ **and** $i \in P_-$ , this representation is not optimal.

Obviously the representation described above can be improved by removing one occurrence of the index $i$ from both multisets.

Although the terms of the task allow the use of one Fibonacci number more than once, it seems natural (GNAQ: well, is it really natural???) that in this way no optimal representation will be obtained. An example from the content of the task ($10 = 5 + 5$) seems to contradict it, because we can also represent the same number differently, this time without repetition: $10 = 8 + 2$ .

​	**Observation 2. ** A representation in which any Fibonacci number occurs at least three times is not optimal. What's more, there is an optimal representation for $k$ in which every Fibonacci number occurs at most once.

​	**Proof.** To justify the above, simple bills based on the definition of the recurrent Fibonacci sequence are sufficient:
$$
\begin{gather}
3F_i = F_{i-2} + (F_{i-1} + F_i ) + F_i
\\
=F_{i-2} + (F_{i+1} + F_i)
\\
= F_{i-2} + F_{i+2} \tag{1}
\\
2F_i = F_{i-2} + (F_{i-1} + F_i)
\\
= F_{i-2} + F{i+1} \tag{2}
\end{gather}
$$
​	By means of operation $(1)$ each triple occurrence of the Fibonacci number can be replaced by the appearance of only two Fibonacci numbers, which of course reduces the size of representation. Such an operation can not, therefore, be feasible in any optimal representation.  However, by means of operation $(2)$, we can gradually eliminate all double occurrences of Fibonacci numbers from the representation, without diminishing the size of the representation. However, you should be more careful here, because after performing the operation $(2)$ , the numbers $F_{i-2}$ and $F_{i+1}$ can occur in the representation many times, so we could potentially get an infinite sequence of deleting double occurrences. It is worth noting, however, that each such operation reduces the sum of the Fibonacci number indices present in the representation by one.   This allows you to make sure that the second type of operation will always be done only finitely times and finally each Fibonacci number will occur in the representation at most once.  (For example, if after performing an operation, the number of $F_2$ occurs twice, we can change its occurrences to $F_3$ and state that the representation was not optimal. )

From the previous considerations, it appears that we can focus on searching for sets (but not multisets) of  $P_+$ and $P_-$, in which we use one Fibonacci number no more than once. In the further part of the description, we will only be interested in such representations.

What's more, it is not difficult to find out that in the optimal representation of numbers, it is not worth using the Fibonacci numbers that are significantly larger than the number $k$. This statement is specified in the following observation. We omit the proof of observation - it will result in proof of correctness of the standard solution.

​	**Observation 3.**  If $F_m \leqslant k  < F_{m+1}$ , then there is an optimal representation of the number $k$ , in which the indexes of Fibonacci numbers do not exceed $m + 1$ .

​	**Observation 4. ** Let $(P_+, P_-)$ be a representation of the number $k$ . If for certain $i$ it occurs:
$$
(a)\,\, i \in P_+ \text{ and } i+1 \in P_+ \text{ or}
\\
(b)\,\, i \in P_= \text{ and } i+1 \in P_- \text{ or}
\\
(c)\,\, i \in P_- \text{ and } i+1 \in P_+ \text{ or}
\\
(d)\,\, i \in P_- \text{ and } i+2 \in P_+
$$
then this representation $(P_+, P_-)$ is not optimal.

​	**Theorem 1.** 设 $F_m \leqslant k \lt F_{m+1}$ ，那么最优分解要么满足 $m\in P_+$，要么满足 $m+1\in P_+$。

​	**Proof.** 如果 $k \leqslant 2$，命题显然成立。假设对于一个 $k\geqslant 3$ ，命题不成立。我们取出 $k$ 的任意一种最优分解 $(P_+,P_-)$，并且设 $z=\max P_+$。根据假设，我们有 $z\ne m \land z\ne m+1$。

​	首先，我们假设 $z\leqslant m-1$。根据 **Observation 4** 的 $(a)$ 一条，我们可以得到的最大的 $k$ 值是 
$$
F_{m-1}+F_{m-3}+F_{m-5}+\cdots
$$
​	显然地，这一串的和小于 $F_m$。（考虑归纳法证明。）我们又有 $F_m\leqslant k$，这种情况不可能。

​	$z\leqslant m-1$ 的情况被排除了。那么反过来，假设 $z\geqslant m+2$。同样根据 **Observation 4** 的 $(b)\, (c)\, (d)$ 三条，我们可以得到的最小的 $k$ 值是
$$
F_{m+2}-F_{m-1}-F_{m-3}-F_{m-5}-\cdots>F_{m+1}
$$
​	然而， $k\lt F_{m+1}$ 。所以这种情况也不成立。命题得证。

这个定理大大减少了我们要讨论的情况。但是不止如此。考虑到 $F_m\leqslant k \lt F_{m+1}$ ，我们可以得出 $k-Fib_m$ 和 $F_{m+1}-k$ 都不超过 $F_{m-1}$（因为 $F_{m+1}-F_m=F_{m-1}$）。

情况立即被大幅减少了。这也用另一种方式得出了 **Observation 3** 的结论（而且比它更强）。那么我们就得到了一种 $O(2^{\frac{m}{2}})$ 的做法：每一步枚举从 $F_{m}$ 和 $F_{m+1}$ 中选择哪一个。

​	**Theorem 2.** Assume that $F_m \leqslant k < F_{m+1}$ . If  $k - F_m \leqslant F_{m+1} -k$, then there is an optimal representation in which $m \in P_+$ .

​	**Proof.**  In the proof, it is enough to limit to the case when $k \geqslant 3$ . Let us mark $a = k - F_m , b = F_{m+1} - k$. Note that if in the representation of the number $k$ we use the component $F_m$ , then it will leave us the number $a$ , and if we use $F_{m + 1}$ , it will leave us $b$ (or $-b$ , but this is basically the same thing). It should therefore be shown that in the case where $a<b$ , the number of components in the optimal representation of the number $a$ is not greater than the number of components necessary to represent the number $b$. Note that $a + b = F{m-1}$ . Consider two cases:

- $a <F_{m-3}$, then $b>F_{m-2}$. By **theorem 1**, we should use the $F_{m-1}$ or $F_{m-2}$ component to try to break down the number $b$. In the first of these cases, we remain with the number $a$ to decompose (using two components, which is unprofitable, because the same situation could happen in one move). If we use the $F_{m-2}$ component, we will have to continue to represent the number $b-F_{m-2}$, however, note that $b-F_{m-2} = F{m-1}-a-F_{m-2} = F_{m-3}-a$, we would have such a move also with $a$. In both cases, it is not worth splitting the number of $b$.
-  $a \geqslant F_{m-3}$ , then $F_{m-3} \leqslant a \leqslant b  \leqslant F_{m-2}$. Based on **theorem 1**, we have two options to consider: the next component of the representation (both cases where we try to further decompose $a$ and $b$) can be either $F_{m-3}$ or $F_{m-2}$. However, $a-F_{m-3} = F_{m-2}-b$ and $F_{m-2}-a = b-F_{m-3}$. Hence, with both $a$ and $b$ we have the same possibilities for further decomposition.

The final conclusion is as follows: the representation of the number $a$ will always require no more operations than the representation of $b$. Thus it is safe to add $m$ to the $P_+$ set and optimally represent what is left.

​	**Theorem 3.**  Let us assume that $F_m \leqslant k < F_{m + 1}$. If $k - F_m> F_{m + 1} - k$ , then there is an optimal representation in which $m + 1 \in P_+$ .

​	**Proof.**  Analogous to the proof of theorem 2. 

The last two propositions suggest for each $k$ the greedy movement to be made. If before this movement occurs $F_m \leqslant k < F_{m + 1}$ (and, let's say, $m> 4$) occurs, then the remaining $k'$ after the movement does not exceed $\max (k - F_m, F_{m + 1} - k )$, that is:
$$
k' \leqslant \frac{F_{m+1}-F_m}{2}=\frac{F_{m-1}}{2}=\frac{F_{m-2}+F{m-3}}{2}<\frac{2F_{m-2}}{2}=F_{m-2}
$$
This shows that after roughly $\frac{m}{3}$ of the movements we get a full representation of the number $k$. Depending on how effectively we implement single movement, we will get a solution with time complexity $O(m^2) = O(\log^2k)$ or $O(m) = O(\log k)$ . Each of these solutions, of course, achieves the maximal point.




