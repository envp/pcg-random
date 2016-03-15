require 'bundler/gem_tasks'
require 'rspec/core/rake_task'

RSpec::Core::RakeTask.new(:spec)

require "rake/extensiontask"

task :build => :compile

Rake::ExtensionTask.new("pcg_random") do |ext|
  ext.lib_dir = "lib/pcg_random"
end

task :cc => [:clean, :compile]

task :default => [:clobber, :compile, :spec]

task :bench do
  PCGBench.press
end