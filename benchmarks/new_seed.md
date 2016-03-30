```bash
Benchmark of Random.new_seed vs PCGRandom.new_seed
==================================================

Benchmark created around: 2016-03-30 14:54:16 +0000

Running for: 100000 iterations

Rehearsal ------------------------------------------------------
Random.new_seed      0.090000   1.240000   1.330000 (  1.323970)
PCGRandom.new_seed   0.100000   1.150000   1.250000 (  1.254944)
--------------------------------------------- total: 2.580000sec

                         user     system      total        real
Random.new_seed      0.110000   1.200000   1.310000 (  1.321571)
PCGRandom.new_seed   0.100000   1.130000   1.230000 (  1.222634)
```
