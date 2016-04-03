### PCGRandom.raw_seed(16)
```bash
Benchmark of Random.raw_seed(16) vs PCGRandom.raw_seed(16)
==================================================

Benchmark created around: 2016-04-03 05:23:54 +0000

Running for: 100000 iterations

Rehearsal ----------------------------------------------------------
Random.raw_seed(16)      0.080000   1.250000   1.330000 (  1.344069)
PCGRandom.raw_seed(16)   0.090000   1.120000   1.210000 (  1.205356)
------------------------------------------------- total: 2.540000sec

                             user     system      total        real
Random.raw_seed(16)      0.080000   1.260000   1.340000 (  1.356403)
PCGRandom.raw_seed(16)   0.100000   1.030000   1.130000 (  1.140350)
```
