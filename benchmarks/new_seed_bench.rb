require 'benchmark'
require 'pcg_random'

# Benchmark of Random.new_seed vs PCGRandom.new_seed
# ==================================================
#
# Benchmark created around: 2016-03-21 17:00:21 +0000
#
# Running for: 100000 iterations
#
# Rehearsal ------------------------------------------------------
# Random.new_seed      0.090000   1.070000   1.160000 (  1.156125)
# PCGRandom.new_seed   0.130000   1.040000   1.170000 (  1.174559)
# --------------------------------------------- total: 2.330000sec
#
#                         user     system      total        real
# Random.new_seed      0.100000   1.080000   1.180000 (  1.185971)
# PCGRandom.new_seed   0.070000   1.050000   1.120000 (  1.115313)

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