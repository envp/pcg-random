# PCGRandom
[![Gem Version](https://badge.fury.io/rb/pcg_random.svg)](https://badge.fury.io/rb/pcg_random)

```
 _____ _____ _____ _____           _           
|  _  |     |   __| __  |___ ___ _| |___ _____ 
|   __|   --|  |  |    -| .'|   | . | . |     |
|__|  |_____|_____|__|__|__,|_|_|___|___|_|_|_|

```

Ruby wrappers for the PCGRandom family of random number generators.

## Installation

### Prerequisites

* A C-compiler (any modern C compiler is supported on *nix, Windows isn't supported yet)
* Modified C source code for pcg_random [available here](https://github.com/vaibhav-y/pcg-c/archive/master.zip) for building libpcg_random. 
* Follow the build instructions [given here](https://github.com/vaibhav-y/pcg-c#building) to build `libpcg_random`

### Installing the gem:

* Rubygems:

``` bash
gem install pcg_random
```

You can also configure the path to `libpcg_random` by specifying it's path explicitly:

``` bash
# specify the custome include path
gem install pcg_random --with-pcg_random-include=directory/containing/pcg_variants.h

# or, specify the custom path to the libpcg_random binary
gem install pcg_random --with-pcg_random-lib=directory/containing/libpcg_random.a

# Or, specify both the lib/ and include/ together to be under path/to/some/directory
gem install pcg_random --with-pcg_random-dir=path/to/some/directory
```

## Development
`TODO: Create a CONTRIBTING.md`

Install pcg_random *from source* using the above steps. Using the above links are important because the library must be compiled with additional flags to be used for gem-development. There are also some issues in the original repository that are addressed in my fork.

## Using the extension

Either jump into your REPL of choice:

``` ruby
~$ irb
2.3.0 :001 > require 'pcg_random'
 => true
```

Or go ahead and try the API, it's built to be as close to `Kernel::Random` as possible!

``` ruby
2.3.0 :002 > seed = PCGRanom.new_seed
 => 315431527813695542666700950080169144774
2.3.0 :003 > rng = PCGRanom.new 1234
 => #<PCGRandom:0x00000001bf3eb0 @seed=1234>
```

For detailed instructions, keep checking this repo, I'm working on getting a wiki up.


## Benchmarks

### PCGRandom.new_seed
```
Benchmark of Random.new_seed vs PCGRandom.new_seed
==================================================

Benchmark created around: 2016-03-30 14:54:16 +0000

Running for: 100000 iterations

Rehearsal ------------------------------------------------------
Random.new_seed      0.090000   1.240000   1.330000 (  1.323970)
PCGRandom.new_seed   0.100000   1.150000   1.250000 (  1.254944)
--------------------------------------------- total: 2.580000sec

                         user     system      total        real
Random.new_seed      0.110000   1.200000   1.310000 (  1.321571)
PCGRandom.new_seed   0.100000   1.130000   1.230000 (  1.222634)
```
### PCGRandom.raw_seed(16)
```
Benchmark of Random.raw_seed(16) vs PCGRandom.raw_seed(16)
==================================================

Benchmark created around: 2016-03-30 14:41:26 +0000

Running for: 100000 iterations

Rehearsal ----------------------------------------------------------
Random.raw_seed(16)      0.080000   1.440000   1.520000 (  1.515513)
PCGRandom.raw_seed(16)   0.110000   1.320000   1.430000 (  1.444519)
------------------------------------------------- total: 2.950000sec

                             user     system      total        real
Random.raw_seed(16)      0.080000   1.470000   1.550000 (  1.563351)
PCGRandom.raw_seed(16)   0.090000   1.340000   1.430000 (  1.441253)
```

## Roadmap

* Achieve full parity with `Kernel::Random`
* Get a wiki explaining how to go about using this gem
* Showcase benchmarks in some other place