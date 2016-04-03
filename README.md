# PCGRandom
[![Gem Version](https://badge.fury.io/rb/pcg_random.svg)](https://badge.fury.io/rb/pcg_random)

```
 _____ _____ _____ _____           _           
|  _  |     |   __| __  |___ ___ _| |___ _____ 
|   __|   --|  |  |    -| .'|   | . | . |     |
|__|  |_____|_____|__|__|__,|_|_|___|___|_|_|_|

```

Ruby wrappers for the PCG (Permuted LCG) family of random number generators.

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

Go ahead and try it, it's built to be as close to `Kernel::Random` as possible!

``` ruby
2.3.0 :002 > seed = PCGRanom.new_seed
 => 315431527813695542666700950080169144774
2.3.0 :003 > rng = PCGRanom.new 1234
 => #<PCGRandom:0x000000022bdf70 @seed=1234>
2.3.0 :004 > rng.rand
 => 0.48717727651819587
2.3.0 :005 > rng.rand 1.618
 => 1.0251792164160871
2.3.0 :006 > rng.rand 189
 => 184
2.3.0 :007 > rng.rand 64499150491713080311265783184370031348
 => 23781278266665729678291694765199065088
```

For detailed instructions, have a look at the [glorious wiki](https://github.com/vaibhav-y/pcg-random/wiki) (Work In Progress™)


## Benchmarks

See [wiki benchmark section](https://github.com/vaibhav-y/pcg-random/wiki/Benchmarks) for detailed benchmarks

## Roadmap

* Achieve parity with `Kernel::Random`
* Make a wiki explaining how to go about using this gem
  - Guide to install `libpcg_random`
  - New contributor's / beginners guide
  - Sample programs
  - Benchmarks vs `Kernel::Random`
* 