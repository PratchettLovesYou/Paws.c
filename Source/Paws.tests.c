# include "Paws.c"
/*  This is the root “tests file.” You can use this to run all of the Paws.c tests, by compiling against `Cest.c`
 *  with `CEST__NO_AUTO` defined:
 *      
 *      C99 -DCEST__NO_AUTO Vendor/Cest.c/Source/Cest.c -IVendor -ISource \
 *        Source/Types/fork/fork.tests.c \
 *        Source/Paws.tests.c \
 *      && ./Paws.tests.o
 *      
 */

# define DECLARATIONS
#   include "Cest.c/Source/Cest.c"
# undef  DECLARATIONS

// This simply constructs the Paws environment (incase you’re not building on `clang` and
// `__attribute__((constructor))` isn’t available... see the discussion in `Paws.c` at `construct()`)
int extern main() { construct(); return Cest.run_all(); }
