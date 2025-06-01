This is repository for computing A052071 and A052072 sequences
```
g++ -Ofast parallel_gmp_cube_search.cpp -o search -lgmpxx -lgmp -fopenmp
```
### Description:
Only math trick used to search _a\_n_ is to check only numbers those cube have fixed length divisible by $n = 8$.
For example for 40-digit numbers one should check around 10 trillion combinations:
$10^13 <= X < (10^40-1)^(\frac{1}{3}) ~ 2.1 \cdot 10^13$

Most of the effort was spent on technical optimizations:
- using GNU MP lib;
- using OMP for multithreading;
- trying to replace multiplications by sums where is is possible;

### Results:
Code is fast enough to compute and verify $a_8$ in 30 hours on laptop, $3 \cdot 10^12$ numbers checked:
$13280759167047^3 = 2342441231418833141828248411332348812823$
