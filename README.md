
About em400
==========================================================================

EM400 is an emulator of Polish MERA-400 minicomputer system (built in late '70 and popular in the '80). Learn more at: http://mera400.pl
In its current state, EM400 can run original MERA-400 software.

Emulation features:

* MERA-400 CPU
* MX-16 CPU (original CPU with modifications)
* real CPU speed
* floating point arithmetic
* Elwro memory (32kword modules, magnetic-core)
* character channel (character-oriented I/O interface)
* SP45DE 8" floppy disk drive
* Amepol MEGA memory (64kword modules, DRAM)
* Amepol MULTIX peripherial processor
* Amepol real time clock
* Winchester disk drive
* terminal connection over TCP or serial line

Things that are still waiting for implementation:

* memory channel and MERA 9425 disk drive
* Terminals connected to MULTIX peripherial processor
* 5.25" floppy disk drive

Things that may or may not be implemented:

* Amepol PLIX peripherial processor
* EC 6051 disk drive
* PT-305 tape drive


Requirements
==========================================================================

To build and run em400 you'll need:

* cmake
* a build tool (GNU make or ninja)
* bison and flex
* Qt6 (used by qt ui)
* libemdas (deassembler library)
* libemcrk (CROOK memory structures)
* libemawp (floating point arithmetic)


Build instructions
==========================================================================

On Linux-based setups, do the following in the source directory:

```
mkdir build
cmake -B build
cmake --build build
cmake --install build
```
On FreeBSD/DFBSD-based setups, you should also include a compatibility shim and ensure the toolchain is configured to point at current libraries:
```
# Here used with GCC 15, as it is a known working version
# On some BSDs, some dependencies of em400 are compiled with old versions of GCC by default
# Hereby it's recommended to add a pair of RPATHs pointing to the compiler libs matching the compiler version you choose to build EM400 with

mkdir build
compat="$(pwd)/src/bsd_compat.h"
cmake -B build \
  -DCMAKE_C_COMPILER=gcc15 \
  -DCMAKE_CXX_COMPILER=g++15 \
  -DCMAKE_BUILD_RPATH=/usr/local/lib/gcc15 \
  -DCMAKE_INSTALL_RPATH=/usr/local/lib/gcc15 \
  -DCMAKE_C_FLAGS="-include $compat" \
  -DCMAKE_CXX_FLAGS="-include $compat"
cmake --build build
cmake --install build

```
In the flags, you can replace version 15 of GCC and G++ with other C/C++ compiler of appropriate version. Any version with full and mature `noexcept` support should work correctly. 

**NOTE: The C and C++ compiler versions should match.**

Running
==========================================================================

EM400 is built with a debugger which currently is its primary user interface.

Usage:

```
em400 [option] ...
```

Where *options* are:

* **-h** - Display help
* **-c config** - Config file to use instead of the default one (*~/.em400/em400.ini*)
* **-p program** - Load program image into OS memory at address 0
* **-l component,component,...** - Enable logging for specified components. Prefix a component with '-' to exclude it (e.g. "all,-cpu"). lib is always logged and cannot be excluded. Available components: lib, app, crk5, mem, cpu, op, int, io, mx, cchr, cmem, uzdat, uzfx, meclo, term, 9425, wnch, flop, pnch, pnrd, tape, all.
* **-L** -  Disable logging
* **-u ui** - User interface to use. Available UIs: qt (default), cmd (minimal, for remote control)
* **-O sec:key=value**  : Override configuration entry "key" in section [sec] with a specific value

