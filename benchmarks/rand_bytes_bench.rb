require 'benchmark'
require 'pcg_random'

Iterations = 100_000
Size = 512

rb_rng = Random.new
pcg_rng = PCGRandom.new

puts "### PCGRandom.bytes(#{Size})"
puts "```bash"
puts "Benchmark of Random.bytes(#{Size}) vs PCGRandom.bytes(#{Size})"
puts "=================================================="
puts ""
puts "Benchmark created around: #{Time.now}"
puts ""
puts "Running for: #{Iterations} iterations"
puts ""
Benchmark.bmbm do |bench|
  bench.report("Random.bytes(#{Size})") do
    Iterations.times {rb_rng.bytes Size}
  end

  bench.report("PCGRandom.bytes(#{Size})") do
    Iterations.times {pcg_rng.bytes Size}
  end
end
puts "```"