require "mkmf"

RbConfig::MAKEFILE_CONFIG['CC'] = ENV['CC'] if ENV['CC']

$CFLAGS = " -Wall -pedantic -ansi -std=c99"

LIBDIR      = RbConfig::CONFIG['libdir']
INCLUDEDIR  = RbConfig::CONFIG['includedir']

HEADER_DIRS = [
  '/opt/local/include',
  '/usr/local/include',
  INCLUDEDIR,
  '/usr/include',
]

LIB_DIRS = [
  '/opt/local/lib',
  '/usr/local/lib',
  LIBDIR,
  '/usr/lib',
]

# Typically, it installs libpcg_random.a to /usr/local/lib and
# pcg_variants.h in /usr/local/include/pcg_variants.h
dir_config('pcg_random', HEADER_DIRS, LIB_DIRS)

abort 'libpcg_random is missing' unless have_library('pcg_random', 'pcg32_random')
abort 'entropy.h missing' unless have_header('entropy.h')
abort 'pcg_variants.h missing' unless have_header('pcg_variants.h')

create_makefile("pcg_random/pcg_random")