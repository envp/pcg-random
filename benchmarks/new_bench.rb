require 'benchmark'
require 'pcg_random'

Iterations = 100_000
Fnum = 42
Bnum = 3640685202844399265562362809129203885

# Default mode
puts "### PCGRandom.new"
puts "```bash"
puts "Benchmark of Random.new vs PCGRandom.new"
puts "=================================================="
puts ""
puts "Benchmark created around: #{Time.now}"
puts ""
puts "Running for: #{Iterations} iterations"
puts ""
Benchmark.bmbm do |bench|
  bench.report("Random.new") do
    Iterations.times {Random.new}
  end

  bench.report("PCGRandom.new") do
    Iterations.times {PCGRandom.new}
  end
end
puts "```"

# With a Fixnum seed
puts "### PCGRandom.new(Fixnum)"
puts "```bash"
puts "Benchmark of Random.new(Fixnum) vs PCGRandom.new(Fixnum)"
puts "=================================================="
puts ""
puts "Benchmark created around: #{Time.now}"
puts ""
puts "Running for: #{Iterations} iterations"
puts ""
Benchmark.bmbm do |bench|
  bench.report("Random.new(Fixnum)") do
    Iterations.times {Random.new(Fnum)}
  end

  bench.report("PCGRandom.new(Fixnum)") do
    Iterations.times {PCGRandom.new(Fnum)}
  end
end
puts "```"


# With a Bignum seed
puts "### PCGRandom.new(Bignum)"
puts "```bash"
puts "Benchmark of Random.new(Bignum) vs PCGRandom.new(Bignum)"
puts "=================================================="
puts ""
puts "Benchmark created around: #{Time.now}"
puts ""
puts "Running for: #{Iterations} iterations"
puts ""
Benchmark.bmbm do |bench|
  bench.report("Random.new(Bignum)") do
    Iterations.times {Random.new(Bnum)}
  end

  bench.report("PCGRandom.new(Bignum)") do
    Iterations.times {PCGRandom.new(Bnum)}
  end
end
puts "```"