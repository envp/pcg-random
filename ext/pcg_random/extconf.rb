require "mkmf"

RbConfig::MAKEFILE_CONFIG['CC'] = ENV['CC'] if ENV['CC']

$CFLAGS = "-Wall -pedantic -ansi -std=c99"

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

abort 'libpcgrandom is missing' unless find_header('pcg_variants.h')
abort 'entropy.h missing' unless find_header('entropy.h')

dir_config('pcg_random', HEADER_DIRS, LIB_DIRS)
create_makefile("pcg_random/pcg_random")