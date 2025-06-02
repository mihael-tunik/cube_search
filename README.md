This is repository for computing A052071 and A052072 sequences.
Build code with:
```
g++ -Ofast parallel_gmp_cube_search.cpp -o search -lgmpxx -lgmp -fopenmp
```
### Description:
Only math trick used to search $a_n$ is to check only numbers those cube have fixed length divisible by $n = 8$.
For $d$-digit number one should check
$(10^{d-1})^{\frac{1}{3}} \leq X \leq (10^{d}-1)^{\frac{1}{3}}$

For 40-digit numbers (where new element of A052072 was found) one should in theory check around 10 trillion combinations:
$10^{13} \leq X < (10^{40}-1)^{\frac{1}{3}} \approx 2.1 \cdot 10^{13}$.

Most of the effort was spent on technical optimizations:
- using GNU MP lib;
- using OMP for multithreading;
- trying to replace multiplications by sums where is is possible;

### Results:
Code is fast enough to compute and verify $a_8$ in 30 hours on laptop, $3 \cdot 10^{12}$ numbers checked:
$13280759167047^3 = 2342441231418833141828248411332348812823$

### Interesting facts:
There's a lot of numerical schemes to speed up computing _consecutive_ cubes, you can try to invent your variation:
- $f_{n+1} = f_{n} + 3 n^2 + 3n + 1$;
- $f_{n+2} = 2 f_{n+1} - f_{n} + 6 (n+1)$;
- $f_{n+3} = 3 f_{n+2} - 3 f_{n+1} + f_n + 6$;
Purpose of this game is to reduce number of multiplications inside main cycle;
