require "mkmf"

$CFLAGS = "-Wall -std=c99"

RbConfig::MAKEFILE_CONFIG['CC'] = ENV['CC'] if ENV['CC']

# Test here if the PCG functions to be wrapped are present.

create_makefile("pcg_random/pcg_random")