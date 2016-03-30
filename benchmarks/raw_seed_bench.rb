require 'benchmark'
require 'pcg_random'

Iterations = 100_000
SeedSize = 16

puts "```bash"
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
puts "```"