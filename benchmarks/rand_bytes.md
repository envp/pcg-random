### PCGRandom.bytes(512)
```bash
Benchmark of Random.bytes(512) vs PCGRandom.bytes(512)
==================================================

Benchmark created around: 2016-04-03 05:49:39 +0000

Running for: 100000 iterations

Rehearsal --------------------------------------------------------
Random.bytes(512)      0.130000   0.020000   0.150000 (  0.155791)
PCGRandom.bytes(512)   0.720000   0.000000   0.720000 (  0.716286)
----------------------------------------------- total: 0.870000sec

                           user     system      total        real
Random.bytes(512)      0.110000   0.010000   0.120000 (  0.119539)
PCGRandom.bytes(512)   0.720000   0.010000   0.730000 (  0.727703)
```
