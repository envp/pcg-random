### PCGRandom#rand
```bash
Benchmark of Random#rand vs PCGRandom#rand
==================================================

Benchmark created around: 2016-04-03 05:44:24 +0000

Running for: 100000 iterations

Rehearsal --------------------------------------------------
Random#rand      0.010000   0.000000   0.010000 (  0.012286)
PCGRandom#rand   0.010000   0.000000   0.010000 (  0.010599)
----------------------------------------- total: 0.020000sec

                     user     system      total        real
Random#rand      0.010000   0.000000   0.010000 (  0.007442)
PCGRandom#rand   0.020000   0.000000   0.020000 (  0.009475)
```
### PCGRandom#rand(Fixnum)
```bash
Benchmark of Random#rand(Fixnum) vs PCGRandom#rand(Fixnum)
==================================================

Benchmark created around: 2016-04-03 05:44:24 +0000

Running for: 100000 iterations

Rehearsal ----------------------------------------------------------
Random#rand(Fixnum)      0.000000   0.000000   0.000000 (  0.009732)
PCGRandom#rand(Fixnum)   0.020000   0.000000   0.020000 (  0.010716)
------------------------------------------------- total: 0.020000sec

                             user     system      total        real
Random#rand(Fixnum)      0.010000   0.000000   0.010000 (  0.009434)
PCGRandom#rand(Fixnum)   0.010000   0.000000   0.010000 (  0.011090)
```
### PCGRandom#rand(Bignum)
```bash
Benchmark of Random#rand(Bignum) vs PCGRandom#rand(Bignum)
==================================================

Benchmark created around: 2016-04-03 05:44:24 +0000

Running for: 100000 iterations

Rehearsal ----------------------------------------------------------
Random#rand(Bignum)      0.030000   0.000000   0.030000 (  0.035028)
PCGRandom#rand(Bignum)   0.030000   0.000000   0.030000 (  0.029023)
------------------------------------------------- total: 0.060000sec

                             user     system      total        real
Random#rand(Bignum)      0.030000   0.000000   0.030000 (  0.033505)
PCGRandom#rand(Bignum)   0.030000   0.000000   0.030000 (  0.030436)
```
### PCGRandom#rand(Float)
```bash
Benchmark of Random#rand(Float) vs PCGRandom#rand(Float)
==================================================

Benchmark created around: 2016-04-03 05:44:24 +0000

Running for: 100000 iterations

Rehearsal ---------------------------------------------------------
Random#rand(Float)      0.010000   0.000000   0.010000 (  0.009500)
PCGRandom#rand(Float)   0.010000   0.000000   0.010000 (  0.012542)
------------------------------------------------ total: 0.020000sec

                            user     system      total        real
Random#rand(Float)      0.010000   0.000000   0.010000 (  0.009108)
PCGRandom#rand(Float)   0.010000   0.000000   0.010000 (  0.012377)
```
