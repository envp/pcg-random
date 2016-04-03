require 'benchmark'
require 'pcg_random'

Iterations = 100_000
puts "### PCGRandom.new_seed"
puts "```bash"
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
puts "```"