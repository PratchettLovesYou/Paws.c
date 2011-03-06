When reading portions of this codebase, there’s a couple of things you should be aware of:

1.  We *really like* using macros to modify how code is passed around. A thorough scan of the `EXTERNALIZE`
    and `DECLARATIONS`/`IMPLEMENTATION` systems will make reading Paws.c source code a *lot* easier, and a *lot*
    more fun. It’s worth your time.
2.  Our ISO C is not your CS teacher’s ISO C, or for that matter, anybody else’s ISO C. It follows a very
    specific series of style guidelines that dictates everything from the alignment of an indirection asterisk to
    the number of space characters between return types and functions’ names. While our code is *not* the C
    you’ve become previously familiar with, it’s *very* clean, beautiful, and readable by comparison. It’s more
    of a bastard child of Ruby and D, than plain ol’ butt-ugly C.

That said, without further ado...

The Sightseer’s Guide to Paws.c
===============================
The Paws.c codebase tends towards oddity; there’s quite a few interesting nooks and crannies you might discover
as you explore. This document will attempt to document your way towards the more unusual or interesting of these.

- Understanding the small CPP macros utilized absolutely *pervasively* throughout this codebase is essential to
  being able to understand the codebase itself. I suggest you start with the thorough documentation of the
  ‘externalization’ system in `Source/Core.h`.
- Our `thing` annotated-pointer type is very central to the implementation of our object system; you can read
  more about it in `Source/Types/Types.h`
- The API bootstrapping spans almost every file in the codebase. You’ll want to start with the `construct()`
  function in `Source/Paws.c` and work your way through the various `register_*` functions defined in each
  individual file.
- Our “tests” are written using a neat little test-running tool named `Cest.`; it’s very self-contained and easy
  to understand. See the source-code in `Vendor/Cest.c`.
- Most of our object system depends on the `fork` nuketype (as you probably know if you’re reading this), and the
  `fork` type depends heavily on our unusual linked-list implementation. See `Source/Types/fork/ll.c`.
