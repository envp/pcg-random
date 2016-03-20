require 'benchmark'
require 'pcg_random'


# Benchmark of Random.new_seed vs PCGRandom.new_seed
# ==================================================
#
# Benchmark created around: 2016-03-20 14:28:07 +0000
#
# Running for: 100000 iterations
#
# Rehearsal ------------------------------------------------------
# Random.new_seed      0.110000   1.030000   1.140000 (  1.135205)
# PCGRandom.new_seed   0.090000   1.060000   1.150000 (  1.157619)
# --------------------------------------------- total: 2.290000sec
#
#                         user     system      total        real
# Random.new_seed      0.090000   1.250000   1.340000 (  1.348947)
# PCGRandom.new_seed   0.150000   1.000000   1.150000 (  1.146167)


Iterations = 100_000

puts "Benchmark of Random.new_seed vs PCGRandom.new_seed"
puts "=================================================="
puts ""
puts "Benchmark created around: #{Time.now}"
puts ""
puts "Running for: #{Iterations} iterations"
puts ""
Benchmark.bmbm do |bench|
  bench.report("Random.new_seed") do
    Iterations.times {Random.new_seed}
  end
  
  bench.report("PCGRandom.new_seed") do
    Iterations.times {PCGRandom.new_seed}
  end
end