`Paws.c`
========
Paws is [@elliottcable][]’s programming language. The design is over a year old, but has gone through
[many iterations][Strata] and changes. There is no working implementation, though several separate codebases are
underway.

This project is my reference implementation. It’s going to be absolutely non-performant at the outset; it is
primarily intended to be an easy-to-peruse codebase that provides a *clean* API for embedding the interpreter
into other projects (statically linked.)

**If you’re interested in Paws, you should join the IRC channel.** There’s no coherent documentation on the
underlying paradigm online; we’ve tried several times to compile such, and had no luck. It’s quite difficult to
explain without an example interpreter to point people to, even on a one-on-basis; nearly impossible to do so
with no example implementation *and* in a generalized anybody-who-reads-this form. (Yes, we know this situation
sucks!)

We’re always available in [**##Paws**][##Paws] on the Freenode IRC network ([click here][webchat] to immediately
open a temporary IRC client.)

  [@elliottcable]: http://twitter.com/elliottcable
  [strata]: https://github.com/Paws/Paws.c/wiki/Strata
  [##Paws]: irc://chat.freenode.net/##Paws
  [webchat]: http://webchat.freenode.net?channels=%23%23Paws

Spelunking
----------
This distribution includes a file that describes many points of interest within the codebase, and should help you
have an easier time exploring it.

If you’re the sort who learns best by reading code instead of docs, head over to the [SPELUNKING][] file!

  [SPELUNKING]: /elliottcable/Paws.c/blob/Master/SPELUNKING.markdown

Compiling
---------
Using the `C99` function below, you can use the following (compatible with `$CC` set to either `clang` or `gcc`,
right now):
    
    # Compiling library (TODO)
    #   (I’ll admit it. I have no idea how to compile a shared library, or even how to make Paws capable of being
    #    compiled as a shared library.)
    
    # Compiling executable (TODO)
    #C99 -ISource \
    #  Source/Types/fork/ll.tests.c \
    #  Source/Types/fork/fork.tests.c \
    #Source/Executable/Paws.c.c && ./Paws.c.o
    
    # Compiling and running all tests
    C99   -IVendor -DCEST__NO_AUTO Vendor/Cest.c/Source/Cest.c   -ISource \
      Source/Types/fork/ll.tests.c \
      Source/Types/fork/fork.tests.c \
    Source/Paws.tests.c && ./Paws.tests.o
    
    # Compiling and running all tests with gdb
    C99 -ggdb   -IVendor -DCEST__NO_AUTO Vendor/Cest.c/Source/Cest.c   -ISource \
      Source/Types/fork/ll.tests.c \
      Source/Types/fork/fork.tests.c \
    Source/Paws.tests.c && gdb -q -batch -x =(echo -e "run\nquit") -se ./Paws.tests.o
    
### Makefile
This project will almost certainly never have a makefile. I love ISO C, and I love the CPP, so don’t
misunderstand me for simply being too pandered-to by modern toolsets to handle the complexity:

**GNU make sucks.**

Just to be clear, SCons sucks too. So do Rake, CMake, and Waf. They all suck, they’re all bloated and overly
verbose, and they all solve the wrong problem (at least for me. To each their own, and all that.)

When it becomes a big enough issue, I’ll probably write a custom buildtool for my C code. Something sleek and
small, with file watchers, SHA1 comparison, git integration, and in-file dependency declaration.

Until then…
    
    zsh; # I’m not very familiar with bash.
    C99() { eval local last="\$$#"; last=${last##*/}; $CC -std=c99 -pedantic-errors -Wall -O0 -o "${last%.*}.o" "$@" }
    
(-;
