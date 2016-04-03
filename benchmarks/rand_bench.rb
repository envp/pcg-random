require 'benchmark'
require 'pcg_random'

Iterations = 100_000
Fnum = 42
Bnum = 3640685202844399265562362809129203885
Flonum = 1606.202844

rb_rng = Random.new
pcg_rng = PCGRandom.new


# Default mode
puts "### PCGRandom#rand"
puts "```bash"
puts "Benchmark of Random#rand vs PCGRandom#rand"
puts "=================================================="
puts ""
puts "Benchmark created around: #{Time.now}"
puts ""
puts "Running for: #{Iterations} iterations"
puts ""
Benchmark.bmbm do |bench|
  bench.report("Random#rand") do
    Iterations.times {rb_rng.rand}
  end

  bench.report("PCGRandom#rand") do
    Iterations.times {pcg_rng.rand}
  end
end
puts "```"

# With a Fixnum bound
puts "### PCGRandom#rand(Fixnum)"
puts "```bash"
puts "Benchmark of Random#rand(Fixnum) vs PCGRandom#rand(Fixnum)"
puts "=================================================="
puts ""
puts "Benchmark created around: #{Time.now}"
puts ""
puts "Running for: #{Iterations} iterations"
puts ""
Benchmark.bmbm do |bench|
  bench.report("Random#rand(Fixnum)") do
    Iterations.times {rb_rng.rand(Fnum)}
  end

  bench.report("PCGRandom#rand(Fixnum)") do
    Iterations.times {pcg_rng.rand(Fnum)}
  end
end
puts "```"


# With a Bignum bound
puts "### PCGRandom#rand(Bignum)"
puts "```bash"
puts "Benchmark of Random#rand(Bignum) vs PCGRandom#rand(Bignum)"
puts "=================================================="
puts ""
puts "Benchmark created around: #{Time.now}"
puts ""
puts "Running for: #{Iterations} iterations"
puts ""
Benchmark.bmbm do |bench|
  bench.report("Random#rand(Bignum)") do
    Iterations.times {rb_rng.rand(Bnum)}
  end

  bench.report("PCGRandom#rand(Bignum)") do
    Iterations.times {pcg_rng.rand(Bnum)}
  end
end
puts "```"

# With a Float bound
puts "### PCGRandom#rand(Float)"
puts "```bash"
puts "Benchmark of Random#rand(Float) vs PCGRandom#rand(Float)"
puts "=================================================="
puts ""
puts "Benchmark created around: #{Time.now}"
puts ""
puts "Running for: #{Iterations} iterations"
puts ""
Benchmark.bmbm do |bench|
  bench.report("Random#rand(Float)") do
    Iterations.times {rb_rng.rand(Flonum)}
  end

  bench.report("PCGRandom#rand(Float)") do
    Iterations.times {pcg_rng.rand(Flonum)}
  end
end
puts "```"