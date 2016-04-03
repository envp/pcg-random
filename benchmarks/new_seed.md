### PCGRandom.new_seed
```bash
Benchmark of Random.new_seed vs PCGRandom.new_seed
==================================================

Benchmark created around: 2016-04-03 05:23:29 +0000

Running for: 100000 iterations

Rehearsal ------------------------------------------------------
Random.new_seed      0.060000   1.040000   1.100000 (  1.106629)
PCGRandom.new_seed   0.080000   1.020000   1.100000 (  1.089735)
--------------------------------------------- total: 2.200000sec

                         user     system      total        real
Random.new_seed      0.070000   1.040000   1.110000 (  1.119493)
PCGRandom.new_seed   0.080000   1.060000   1.140000 (  1.135289)
```
