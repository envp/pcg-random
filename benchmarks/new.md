### PCGRandom.new
```bash
Benchmark of Random.new vs PCGRandom.new
==================================================

Benchmark created around: 2016-04-03 05:41:36 +0000

Running for: 100000 iterations

Rehearsal -------------------------------------------------
Random.new      0.890000   1.150000   2.040000 (  2.045790)
PCGRandom.new   0.640000   0.990000   1.630000 (  1.626109)
---------------------------------------- total: 3.670000sec

                    user     system      total        real
Random.new      0.900000   1.110000   2.010000 (  2.029475)
PCGRandom.new   0.520000   1.170000   1.690000 (  1.698575)
```
### PCGRandom.new(Fixnum)
```bash
Benchmark of Random.new(Fixnum) vs PCGRandom.new(Fixnum)
==================================================

Benchmark created around: 2016-04-03 05:41:43 +0000

Running for: 100000 iterations

Rehearsal ---------------------------------------------------------
Random.new(Fixnum)      0.310000   0.030000   0.340000 (  0.343708)
PCGRandom.new(Fixnum)   0.210000   0.010000   0.220000 (  0.214261)
------------------------------------------------ total: 0.560000sec

                            user     system      total        real
Random.new(Fixnum)      0.270000   0.020000   0.290000 (  0.292531)
PCGRandom.new(Fixnum)   0.190000   0.000000   0.190000 (  0.192535)
```
### PCGRandom.new(Bignum)
```bash
Benchmark of Random.new(Bignum) vs PCGRandom.new(Bignum)
==================================================

Benchmark created around: 2016-04-03 05:41:44 +0000

Running for: 100000 iterations

Rehearsal ---------------------------------------------------------
Random.new(Bignum)      0.700000   0.040000   0.740000 (  0.735335)
PCGRandom.new(Bignum)   0.230000   0.000000   0.230000 (  0.239785)
------------------------------------------------ total: 0.970000sec

                            user     system      total        real
Random.new(Bignum)      0.710000   0.020000   0.730000 (  0.733759)
PCGRandom.new(Bignum)   0.210000   0.000000   0.210000 (  0.209087)
```
