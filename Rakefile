require 'bundler/gem_tasks'
require 'bundler'
require 'rspec/core/rake_task'
require "rake/extensiontask"

RSpec::Core::RakeTask.new(:spec)

Rake::ExtensionTask.new("pcg_random") do |ext|
  ext.lib_dir = "lib/pcg_random"
end

task :build => :compile
task :cc => [:clean, :compile]
task :default => [:clobber, :compile, :spec]