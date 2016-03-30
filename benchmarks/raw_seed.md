```bash
Benchmark of Random.raw_seed(16) vs PCGRandom.raw_seed(16)
==================================================

Benchmark created around: 2016-03-25 18:27:35 +0000

Running for: 100000 iterations

Rehearsal ----------------------------------------------------------
Random.raw_seed(16)      0.040000   0.980000   1.020000 (  1.031410)
PCGRandom.raw_seed(16)   0.050000   0.970000   1.020000 (  1.021024)
------------------------------------------------- total: 2.040000sec

                             user     system      total        real
Random.raw_seed(16)      0.090000   0.990000   1.080000 (  1.076778)
PCGRandom.raw_seed(16)   0.060000   1.000000   1.060000 (  1.067268)
```
