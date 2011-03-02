`Paws.c`
========
Welcome to the new world.

Compiling
---------

### Makefile
This project will almost certainly never have a makefile. I love ISO C, and I love the CPP, so don’t
misunderstand me for simply being too pandered-to by modern toolsets to handle the complexity:

**GNU make sucks.**

Just to be clear, SCons sucks too. So do Rake, CMake, and Waf. They all suck, they’re all bloated and overly
verbose, and they all solve the wrong problem (at least for me. To each their own, and all that.)

When it becomes a big enough issue, I’ll probably write a custom buildtool for my C code. Something sleek and
small, with file watchers, SHA1 comparison, git integration, and in-file dependency declaration.

Until then…
    
    zsh;
    C99() { eval local last="\$$#"; last=${last##*/}; clang -std=c99 -pedantic-errors -Wall -O0 -o "${last%.*}.o" "$@" }
    
(-;
