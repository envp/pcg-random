require 'benchmark'
require 'pcg_random'


# Benchmark of Random.raw_seed(16) vs PCGRandom.raw_seed(16)
# ==================================================
#
# Benchmark created around: 2016-03-20 14:34:40 +0000
#
# Running for: 100000 iterations
#
# Rehearsal ----------------------------------------------------------
# Random.raw_seed(16)      0.060000   1.110000   1.170000 (  1.173924)
# PCGRandom.raw_seed(16)   0.060000   1.110000   1.170000 (  1.175782)
# ------------------------------------------------- total: 2.340000sec
#
#                             user     system      total        real
# Random.raw_seed(16)      0.060000   1.230000   1.290000 (  1.292141)
# PCGRandom.raw_seed(16)   0.080000   1.100000   1.180000 (  1.189046)



Iterations = 100_000
SeedSize = 16
puts "Benchmark of Random.raw_seed(#{SeedSize}) vs PCGRandom.raw_seed(#{SeedSize})"
puts "=================================================="
puts ""
puts "Benchmark created around: #{Time.now}"
puts ""
puts "Running for: #{Iterations} iterations"
puts ""
Benchmark.bmbm do |bench|
  bench.report("Random.raw_seed(#{SeedSize})") do
    Iterations.times {Random.raw_seed SeedSize}
  end
  
  bench.report("PCGRandom.raw_seed(#{SeedSize})") do
    Iterations.times {PCGRandom.raw_seed SeedSize}
  end
end