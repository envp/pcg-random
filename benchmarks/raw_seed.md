```bash
Benchmark of Random.raw_seed(16) vs PCGRandom.raw_seed(16)
==================================================

Benchmark created around: 2016-03-30 14:41:26 +0000

Running for: 100000 iterations

Rehearsal ----------------------------------------------------------
Random.raw_seed(16)      0.080000   1.440000   1.520000 (  1.515513)
PCGRandom.raw_seed(16)   0.110000   1.320000   1.430000 (  1.444519)
------------------------------------------------- total: 2.950000sec

                             user     system      total        real
Random.raw_seed(16)      0.080000   1.470000   1.550000 (  1.563351)
PCGRandom.raw_seed(16)   0.090000   1.340000   1.430000 (  1.441253)
```
