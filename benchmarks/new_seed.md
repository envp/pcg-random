```bash
Benchmark of Random.new_seed vs PCGRandom.new_seed
==================================================

Benchmark created around: 2016-03-25 18:27:27 +0000

Running for: 100000 iterations

Rehearsal ------------------------------------------------------
Random.new_seed      0.120000   1.060000   1.180000 (  1.173928)
PCGRandom.new_seed   0.070000   1.020000   1.090000 (  1.096108)
--------------------------------------------- total: 2.270000sec

                         user     system      total        real
Random.new_seed      0.100000   1.090000   1.190000 (  1.188864)
PCGRandom.new_seed   0.110000   1.090000   1.200000 (  1.197528)
```
