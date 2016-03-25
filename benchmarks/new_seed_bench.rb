require 'benchmark'
require 'pcg_random'

# Benchmark of Random.new_seed vs PCGRandom.new_seed
# ==================================================
#
# Benchmark created around: 2016-03-24 18:20:57 +0000
#
# Running for: 100000 iterations
#
# Rehearsal ------------------------------------------------------
# Random.new_seed      0.100000   1.040000   1.140000 (  1.132634)
# PCGRandom.new_seed   0.080000   1.000000   1.080000 (  1.088872)
# --------------------------------------------- total: 2.220000sec
#
#                         user     system      total        real
# Random.new_seed      0.080000   1.030000   1.110000 (  1.107880)
# PCGRandom.new_seed   0.130000   0.980000   1.110000 (  1.102163)


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